#pragma once

/* ------ INFOS ------ *\
author: Robin Modisch

desc: This class is used to manage all components for a selfmade clock.

---------- TODO ----------
1. Everything
2. Singleton? IO needs to be


*\ --------------------*/

#include "LED_manager.h"    // FastLED wrapper
#include "RTC_manager.h"    // clock module get/set
#include "HW_manager.h"     // IO & more


class clock_manager
{
private:
    LED_manager leds;
    RTC_manager rtc;
    HW_manager hw;
    

public:
    clock_manager();
    tick();     // time as parameter?



}
