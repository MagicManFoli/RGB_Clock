#include "clock_manager.h"

#include <Arduino.h>
#include "settings.h"

clock_manager::clock_manager()
{
    this->register_buttons();
}

void clock_manager::tick()
{
    if (debug) show_cycletime();
}

// ------ private -------------

void clock_manager::register_buttons()
{
    /*
    hw.BT1 = &this.incHour();
    hw.BT2 = &this.incMinute();
    hw.BT3 = &this.dimLight();
    */
}

void clock_manager::incHour()
{
    // don't forget wraparound

}

void clock_manager::incMinute()
{
    // add leds.get_n_leds()/60 minutes

}

void clock_manager::show_cycletime()
{
    // define last value to get difference
    static unsigned long last_call = 0;

    unsigned long now = millis();

    Serial.print(F("cycle time: "));
    Serial.print(now - last_call);
    Serial.println(F(" ms"));

    last_call = now;
}
