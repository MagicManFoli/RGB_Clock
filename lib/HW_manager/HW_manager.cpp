#include "HW_manager.h"



HW_manager::HW_manager()
{



}

void HW_manager::add_listener(uint8_t index, f_listener handler)
{
    listener_list[index] = &handler;

}



// ----------- private ----------

void HW_manager::call_BT(uint8_t index)
{
    // unpack function pointer from list and call
    (*listener_list[index])();
}

