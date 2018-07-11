
/* ------ INFOS ------ *\

This program controls a selfmade clock based around RGB-LEDs

@author: Robin Modisch, Sven Kiebler
@version: 0.1

---------- TODO ----------
1. Everything

*\ --------------------*/

#include <Arduino.h>

#include "settings.h"
#include "clock_manager.h"

clock_manager clock;

// put your setup code here, to run once:
void setup() 
{
    if (debug)
    {
        Serial.begin(9600);
        Serial.println();
        Serial.println(F("Welcome to RGB_clock"));
        Serial.println(F("Debug mode is activated"));
    } 
}

// put your main code here, to run repeatedly:
void loop() 
{
    clock.tick();




    // wait for human interaction time 
    if (debug) delay(2000);    
}