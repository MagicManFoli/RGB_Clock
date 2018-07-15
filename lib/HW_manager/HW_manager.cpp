#include "HW_manager.h"

// initialise static
f_listener *HW_manager::listener_list[n_buttons];

volatile bool HW_manager::state_changed = false;
volatile bool HW_manager::changed[n_buttons] = {false};
volatile bool HW_manager::last_states[n_buttons] = {false};
volatile unsigned long HW_manager::last_trigger = millis();

void HW_manager::add_listener(uint8_t index, f_listener handler)
{
    if (debug) 
    {
        Serial.print(F("adding listener for "));
        Serial.println(index);
    }

    listener_list[index] = &handler;
}

void HW_manager::check_change()
{
    
    //something has changed, find out what
    if (state_changed)
    {


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
                //HW_manager::call_listener(last_pressed);
            }
        }

        state_changed = false;
    }
}

bool* HW_manager::get_button_states()
{
    static bool curr_states[n_buttons];

    // save all button states
    for (uint8_t i = 0; i < n_buttons; i++)
    {
        curr_states[i] = !digitalRead(buttons[i]); // inverted attachment
    }

    return curr_states;
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
        attachInterrupt(digitalPinToInterrupt(buttons[i]), handle_interrupt, FALLING);
    }

    pinMode(LED_BUILTIN, OUTPUT);
}

// called when pulled to GND
void HW_manager::handle_interrupt()
{
    // save current time as reference
    unsigned long now = millis();

    // first change is always correct, get button-snapshot
    bool *curr_states = get_button_states();

    // millis had wraparound, rare corner case
    if (last_trigger > now )    // every 49 days
    {
        last_trigger = now;
    }

    // -- ignore second call from bouncing

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
        if (curr_states[i] != last_states[i])
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

    // works like a return value
    state_changed = true;
}

void HW_manager::call_listener(uint8_t index)
{
    // unpack function pointer from list and call
    (*listener_list[index])();
}

