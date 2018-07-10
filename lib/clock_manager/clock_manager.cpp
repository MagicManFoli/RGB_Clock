#include "clock_manager.h"



clock_manager::clock_manager()
{
    this->register_buttons();
}

void clock_manager::tick()
{
    // define last value to get difference
    unsigned long now = millis();
    unsigned long delta_t = now - last_call;

    if (debug) print_looptime(delta_t);

    last_call = now;
}

// ------ private -------------

void clock_manager::register_buttons()
{
    hw.add_listener(0, &(this->incHour));

}

void clock_manager::incHour()
{
    // don't forget wraparound
    if (debug) Serial.println(F("incHour"));
}

void clock_manager::incMinute()
{
    // add leds.get_n_leds()/60 minutes

}

void clock_manager::print_looptime(unsigned long delta_t)
{
    Serial.print(F("cycle time: "));
    Serial.print(delta_t);
    Serial.println(F(" ms"));
}
