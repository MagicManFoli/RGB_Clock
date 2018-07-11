#include "HW_manager.h"

// initialise static
f_listener *HW_manager::listener_list[n_buttons];
volatile uint8_t HW_manager::last_pressed = 255;

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
    for (int i=0; i < n_buttons; i++)
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

void HW_manager::handle_interrupt()
{
    // debounce

    // find out which button was pressed

    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    last_pressed = 2;
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

        //HW_manager::call_BT(last_pressed);
        last_pressed = 255;
    }
}

void HW_manager::call_BT(uint8_t index)
{
    // unpack function pointer from list and call
    (*listener_list[index])();
}

