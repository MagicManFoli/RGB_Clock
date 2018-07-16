
/* ------ INFOS ------ *\

This program controls a selfmade clock based around RGB-LEDs

@author: Robin Modisch, Sven Kiebler
@version: 0.1

---------- TODO ----------
1. Everything
2. I've done it better


*\ --------------------*/

#include <Arduino.h>

#include "settings.h"
#include "clock_manager.h"

//clock_manager clock;

// put your setup code here, to run once:
void setup() 
{
    if (debug)
    {
        Serial.begin(115200);
        Serial.println();
        Serial.println(F("Welcome to RGB_clock"));
        Serial.println(F("Debug mode is activated"));
    } 

    // connect RGBs
    LED_manager::setup();

    // connect clock manager to hardware_manager
    clock_manager::register_buttons();

    // connect physical buttons
    HW_manager::attach_interrupts();

    if (debug) delay(1000);
}

// put your main code here, to run repeatedly:
void loop() 
{
    clock_manager::tick();

    // wait for human interaction time 
    //if (debug) delay(1000);    
}