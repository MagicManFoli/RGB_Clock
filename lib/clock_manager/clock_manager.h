#pragma once

/** ------ INFOS ------ *\

This class is used to manage all components for a selfmade clock.



@author: Robin Modisch
@version: 0.1

---------- TODO ----------

- decoding of H:M to LEDs in clock or LED?
    both need to know number of LEDs
- move incHour/Minute to RTC?
- move dim_light to LED?

- what use has a fully static class compared to a namespace?
    global variables?

*\ --------------------*/

#include <Arduino.h>
#include "settings.h"

#include "LED_manager.h"    // FastLED wrapper
#include "RTC_manager.h"    // clock module get/set
#include "HW_manager.h"     // IO & more


class clock_manager
{
    private:
/*
        LED_manager leds;
        RTC_manager rtc;
        HW_manager hw;
*/
        // used to estimate loop time
        static unsigned long last_call;

        /**
         * reads rtc hour, increments by one and writes back
         * then updates LEDs
         * 
         */
        static void inc_hour();

        /**
         * same as inHour, just for minutes
         * 
         * 
         */
        static void inc_minute();

        /**
         * change brightness
         * 
         * 
         */
        static void dim_light();

        /**
         * debug function, prints duration of one tick to Serial
         * 
         */
        static void print_looptime(unsigned long delta_t);

    public:
        clock_manager() = delete;


        /**
         * this function registers this classes function at the hardware manager.
         * 
         * BT1 = Hour++
         * BT2 = Minute++
         * BT3 = 
         * 
         */
        static void register_buttons();

        /**
         * looping execution of main thread, called from loop
         * 
         * @param ?? // time as parameter?
         * @return nothing
         */
        static void tick();

    //protected:
};

