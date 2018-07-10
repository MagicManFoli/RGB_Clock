#pragma once

/** ------ INFOS ------ *\

this file is used to set global parameters for all modules

---------- TODO ----------
- move this to parent directory?

*\ --------------------*/

#include <Arduino.h>
#include <stdint.h>

// activate or deactivate helper segments
#define debug true

const uint8_t n_leds = 24;
const uint8_t n_buttons = 3;