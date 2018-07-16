#include "LED_manager.h"

// start white
CRGB LED_manager::RGBs[n_leds] = {CRGB::White};

// start with medium
uint8_t LED_manager::brightness_index = n_brightness/2;

void LED_manager::setup()
{
    // neopixel already have RGB corrected for WS2812B
    FastLED.addLeds<NEOPIXEL,pin_data>(RGBs, n_leds);

    // all white for start
    fill_solid(RGBs, n_leds, CRGB::OrangeRed);

    // show with default brightness
    FastLED.setBrightness(brightness_levels[brightness_index]);
    FastLED.show();
}

void LED_manager::next_brightness()
{
    brightness_index++;

    // wraparound
    if (brightness_index >= n_brightness) brightness_index -= n_brightness;

    uint8_t brightness = brightness_levels[brightness_index];

    if (led_debug) 
    {
        Serial.print(F("next_brightness: "));
        Serial.println(brightness);
    }

    FastLED.setBrightness(brightness);
    FastLED.show();
}



