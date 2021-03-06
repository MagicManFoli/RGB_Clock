#pragma once

/* ------ INFOS ------ *\

This class manages the hardware, notably the three buttons used.

Implementation in statics because interrupts can't be member functions

buttons are counted in rows from top left to bottom right, starting at 0
Short input to GND to trigger

Board | Function                 | ESP8266 Pin
----------------------------------------------
|TX |TXD                         |TXD   |
|RX |RXD                         |RXD   |
|A0 |Analog input, max 3.3V input|A0    |
|D0 |IO                          |GPIO16|
|D1 |IO, SCL                     |GPIO5 |
|D2 |IO, SDA                     |GPIO4 |
|D3 |IO, 10k Pull-up             |GPIO0 |
|D4 |IO, 10k Pull-up, BUILTIN_LED|GPIO2 |
|D5 |IO, SCK                     |GPIO14|
|D6 |IO, MISO                    |GPIO12|
|D7 |IO, MOSI                    |GPIO13|
|D8 |IO, 10k Pull-down, SS       |GPIO15|
|G  |Ground                      |GND   |
|5V |5V                          |-     |
|3V3|3.3V                        |3.3V  |
|RST|Reset                       |RST   |

Buttons used in code are from the right side, connected to left

@author: Robin Modisch
@version: 0.7

---------- TODO ----------
1. first button lost

*\ --------------------*/

#include <Arduino.h>
#include "settings.h"

// definition for all handlers 
typedef void (*f_listener)();

class HW_manager
{
private:
    //static HW_manager *instance;

    // list of pointers to handlers, index of list is index of button
    static f_listener listener_list[n_buttons];

    static volatile bool state_changed;
    static volatile bool changed[n_buttons];
    static volatile bool last_states[n_buttons];

    /**
     * debounce and check which button was pressed
     * 
     * refreshes state_changed, changed and last_states
     * 
     */
    static void handle_interrupt();

    /**
     * intermediate function to be called from code to signal a button press
     * 
     * @param index index of physical button
     * @return success
     */
    static bool call_listener(const uint8_t index);

public:
    // static class, no initialisation
    HW_manager() = delete;    

    /**
     * attaches interrupts to physical channels
     * 
     */
    static void attach_interrupts();

    /**
     * add handler to be called when a button was pressed
     * 
     * @param index index of physical button
     * @param handler function to be called when button was pressed
     * @return success
     */
    static bool add_listener(const uint8_t index, const f_listener handler);

    /**
     * 
     * poll interrupt changes from main loop
     * Never start from ISR!
     * 
     */
    static void check_change();

    /**
     * read button states from port & return
     * 
     * @return pointer to array of corrected states of buttons
     */
    static const bool* get_button_states();

    static void print_array(const volatile bool* array);
};

