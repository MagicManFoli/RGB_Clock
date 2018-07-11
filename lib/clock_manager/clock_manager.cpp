#include "clock_manager.h"



clock_manager::clock_manager()
{
    clock_manager::clock = this;

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
    hw.add_listener(0, &(clock->inc_hour));
    hw.add_listener(1, &(clock->inc_minute));
    //hw.add_listener(2, &(clock->DimLight));
}

void clock_manager::inc_hour()
{
    // don't forget wraparound
    if (debug) Serial.println(F("incHour"));
}

void clock_manager::inc_minute()
{
    // add leds.get_n_leds()/60 minutes

}

void clock_manager::print_looptime(unsigned long delta_t)
{
    Serial.print(F("cycle time: "));
    Serial.print(delta_t);
    Serial.println(F(" ms"));
}
