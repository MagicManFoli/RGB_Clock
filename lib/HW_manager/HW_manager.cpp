#include "HW_manager.h"


HW_manager::HW_manager()
{
    HW_manager::hw = this;

    
}


void HW_manager::add_listener(uint8_t index, f_listener handler)
{
    listener_list[index] = &handler;
}



// ----------- private ----------

void HW_manager::attach_interrupts()
{
    // attach each interrupt pin from list
    for (int i=0; i < n_buttons; i++)
    {
        pinMode(buttons[i], INPUT_PULLUP);  // trigger with GND
        attachInterrupt(digitalPinToInterrupt(buttons[i]), handle_interrupt, FALLING);
    }
}

void HW_manager::handle_interrupt()
{
    // find out which button was pressed

    hw->call_BT(1);
}

void HW_manager::call_BT(uint8_t index)
{
    // unpack function pointer from list and call
    (*listener_list[index])();
}

