#pragma once

/* ------ INFOS ------ *\

This class manages the hardware, notably the three buttons used.

buttons are counted in rows from top left to bottom right, starting at 0

@author: ??
@version: 0.0

---------- TODO ----------
1. Everything

*\ --------------------*/

#include <Arduino.h>
#include "settings.h"

// definition for all handlers 
typedef void (*f_listener)();

class HW_manager
{
private:
    // list of pointers to handlers, index of list is index of button
    f_listener *listener_list[n_buttons];


    /**
     * intermediate function to be called from code to signal a button press
     * 
     * @param index index of physical button
     */
    void call_BT(uint8_t index);

public:

    HW_manager();

    /**
     * add handler to be called when a button was pressed
     * 
     * @param index index of physical button
     * @param handler function to be called when button was pressed
     */
    void add_listener(uint8_t index, f_listener handler);

};