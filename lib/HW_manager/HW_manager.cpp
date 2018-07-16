#include "HW_manager.h"

// initialise static
f_listener *HW_manager::listener_list[n_buttons] = {NULL};

volatile bool HW_manager::state_changed = false;
volatile bool HW_manager::changed[n_buttons] = {false};
volatile bool HW_manager::last_states[n_buttons] = {false};

bool HW_manager::add_listener(uint8_t index, f_listener handler)
{
    if (index >= n_buttons) return false;

    if (debug) 
    {
        Serial.print(F("adding listener for "));
        Serial.println(index);
    }

    listener_list[index] = &handler;

    return true;
}

void HW_manager::check_change()
{
    
    //something has changed, find out what
    if (state_changed)
    {
        if(debug) 
        {
            Serial.print(F("curr_states: "));
            print_array(get_button_states());

            Serial.print(F("last_states: "));
            print_array(last_states);

            Serial.print(F("changed:     "));
            print_array(changed);
        }

        //call every changed
        for (uint8_t i = 0; i < n_buttons; i++)
        {
            if (changed[i])
            {   
                //reset 
                changed[i] = false;

                if (debug)
                {
                    Serial.print(F("Button pressed: "));
                    Serial.println(i);
                }

                //TODO what is wrong with this?
                //HW_manager::call_listener(i);
            }
        }

        state_changed = false;
    }
}

const bool* HW_manager::get_button_states()
{
    static bool curr_states[n_buttons];

    // save all button states
    for (uint8_t i = 0; i < n_buttons; i++)
    {
        curr_states[i] = !digitalRead(buttons[i]); // inverted attachment
    }

    return curr_states;
}

void HW_manager::print_array(const volatile bool* array)
{
    // print all
    for (uint8_t i = 0; i < n_buttons; i++)
    {
        Serial.print(i);
        Serial.print(F(" = "));
        Serial.print(array[i]);
        Serial.print(F(", "));
    }
    Serial.println(F("; "));
}

// ----------- private ----------

void HW_manager::attach_interrupts()
{
    if (debug) 
    {
        Serial.print(F("n_buttons: "));
        Serial.println(n_buttons);
    }

    // attach each interrupt pin from list
    for (uint8_t i=0; i < n_buttons; i++)
    {
        if (debug)
        {
            Serial.print(F("attaching interrupt at "));
            Serial.println(buttons[i]);
        }
        pinMode(buttons[i], INPUT_PULLUP);  // trigger with GND
        // invert flank logic because of inverted trigger
        attachInterrupt(digitalPinToInterrupt(buttons[i]), handle_interrupt, CHANGE);
    }

    pinMode(LED_BUILTIN, OUTPUT);
}

// called when pulled to GND
void HW_manager::handle_interrupt()
{
    static volatile unsigned long last_trigger = millis();

    // save current time as reference
    unsigned long now = millis();

    // first change is always correct, get button-snapshot
    // make sure to not modify it, pointer from function
    const bool *curr_states = get_button_states();

    // millis had wraparound, rare corner case
    if (last_trigger > now )    // every 49 days
    {
        last_trigger = now;
        return;
    }

    // -- ignore second+ call from bouncing

    // called too soon, must be bounce
    if ((now - last_trigger) < t_debounce )  
    {
        last_trigger = now; // update for next bounce
        return;
    }

    last_trigger = now; // update for next bounce

    // -- stable, using it

    // find out which button had flank
    for (uint8_t i = 0; i < n_buttons; i++)
    {
        // found pin with positive flank
        if (last_states[i] != curr_states[i])
        {
            // prevent second processing & reset
            last_states[i] = curr_states[i];

            // only use positive flank
            if (curr_states[i] == true)
            {
                // mark state changed for following logic
                state_changed = true;

                // save changed pins
                changed[i] = true;
            }
        }
    }

    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

bool HW_manager::call_listener(uint8_t index)
{
    if (index >= n_buttons) return false;

    // check for value
    if (listener_list[index] == NULL) 
    {
        if (debug) Serial.println(F("Listener not initialised"));
        return false;
    }
    // unpack function pointer from list and call
    (*listener_list[index])();

    return true;
}

