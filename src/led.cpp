#include <Arduino.h>
#include <string.h>

#include "led.h"
#include "config.h"

void Led::setup() {
    FastLED.addLeds<WS2812B, LED_PORT, GRB>(Led::ids, 0, NUM_LEDS);
    // 0-255 value range for 0-100%
    FastLED.setBrightness(10);

    for(int i = 0; i < NUM_LEDS; i++) {
        Led::ids[i].setRGB(0, 0, 0);
    }

    FastLED.show();
}