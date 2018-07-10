#pragma once

/** ------ INFOS ------ *\

This class is used to manage all components for a selfmade clock.



@author: Robin Modisch
@version: 0.1

---------- TODO ----------

- decoding of H:M to LEDs in clock or LED?
    both need to know number of LEDs
- Singleton? IO definitely needs to be
- move incHour/Minute to RTC?
- listeners need to be static, members not allowed
    -> make everything static or find clever differentiation?

*\ --------------------*/

#include <Arduino.h>
#include "settings.h"

#include "LED_manager.h"    // FastLED wrapper
#include "RTC_manager.h"    // clock module get/set
#include "HW_manager.h"     // IO & more


class clock_manager
{
    public:
        clock_manager();

        /**
         * looping execution of main thread, called from loop
         * 
         * @param ?? // time as parameter?
         * @return nothing
         */
        void tick();

    //protected:

    private:
        LED_manager leds;
        RTC_manager rtc;
        HW_manager hw;

        // used to estimate loop time
        unsigned long last_call = 0;

        /**
         * this function registers this classes function at the hardware manager.
         * 
         * BT1 = Hour++
         * BT2 = Minute++
         * BT3 = 
         * 
         */
        void register_buttons();

        /**
         * reads rtc hour, increments by one and writes back
         * then updates LEDs
         * 
         */
        void incHour();

        /**
         * same as inHour, just for minutes
         * 
         * 
         */
        void incMinute();

        /**
         * debug function, prints duration of one tick to Serial
         * 
         */
        void print_looptime(unsigned long delta_t);
};
