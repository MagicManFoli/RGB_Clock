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

#define hw_debug false



const uint8_t n_leds = 24;

const uint8_t buttons[] = {D5, D6, D7};
const uint8_t n_buttons = sizeof(buttons)/sizeof(uint8_t);  //automatic

// time to wait for stable signal in ms (adafruit says 5+ ms)
const uint16_t t_debounce = 50;

