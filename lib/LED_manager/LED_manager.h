#pragma once

#include <stdint.h>

/* ------ INFOS ------ *\
This class manages all interactions with the LEDs.
This class could be without static, but listeners require static functions
-> prevents multiple stripes but enables loose coupling

@author: Robin Modisch
@version: 0.1

---------- TODO ----------
1. get time through call or get from millis()?
2. fading from tick or time settings calls?
3. fix warning from softwareserial

*\ --------------------*/

#include <Arduino.h>
#include "settings.h"

// disable messages
#define FASTLED_INTERNAL
#include <FastLED.h>

class LED_manager
{
    private:

        static CRGB RGBs[n_leds];
        static uint8_t brightness_index;

    public:

        /**
         * new constructor
         * 
         */
        static void setup();

        /**
         * controls fading & Co
         * 
         */
        static void tick();

        /**
         * change brightness in reasonable steps
         * 
         * 
         */
        static void next_brightness();

};

