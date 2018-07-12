#include "HW_manager.h"

// initialise static
f_listener *HW_manager::listener_list[n_buttons];
volatile uint8_t HW_manager::last_pressed = 255;
volatile bool HW_manager::last_states[n_buttons] = {false};
volatile unsigned long HW_manager::last_trigger[n_buttons] = {0};

void HW_manager::add_listener(uint8_t index, f_listener handler)
{
    if (debug) 
    {
        Serial.print(F("adding listener for "));
        Serial.println(index);
    }

    listener_list[index] = &handler;
}

// ----------- private ----------

void HW_manager::attach_interrupts()
{

    // attach each interrupt pin from list
    for (uint8_t i=0; i < n_buttons; i++)
    {
        if (debug)
        {
            Serial.print(F("attaching interrupt at "));
            Serial.println(buttons[i]);
        }
        pinMode(buttons[i], INPUT_PULLUP);  // trigger with GND
        attachInterrupt(digitalPinToInterrupt(buttons[i]), handle_interrupt, FALLING);
    }

    pinMode(LED_BUILTIN, OUTPUT);
}

// called when pulled to GND
void HW_manager::handle_interrupt()
{

    // find out which button was pressed

    uint8_t index = 255;    // unrealistic default

    // check all buttons
    for (uint8_t i = 0; i < n_buttons; i++)
    {
        // found changed pin
        if (last_states[i] != !digitalRead(buttons[i])) // should be !0 == 1
        {
            index = i;
            last_states[i] = !digitalRead(buttons[i]);
            break;
        }
    }

    //if (debug && index == 255) Serial.println(F("err: no index found"));

    // save current time as reference
    unsigned long now = millis();

    // still bouncing
    if ((now - last_trigger[index]) < t_debounce )  
    {
        last_trigger[index] = now; // update for next bounce
        return;
    }

    last_trigger[index] = now; // update for next bounce

    // stable, using it
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    last_pressed = index;
}

void HW_manager::check_change()
{
    if (last_pressed != 255)
    {
        if (debug)  
        {
            Serial.print(F("Button pressed: "));
            Serial.println(last_pressed);
        }

        //TODO what is wrong with this?
        //HW_manager::call_listener(last_pressed);
        last_pressed = 255;
    }
}

void HW_manager::call_listener(uint8_t index)
{
    // unpack function pointer from list and call
    (*listener_list[index])();
}

