#ifndef LED_H
#define LED_H

#include <FastLED.h>


class Led {
    
    private:
        static CRGB ids[];

        static void fire();
        static void rainbow(uint8_t, uint8_t);
    public:
        
        static int display_mode;
        static void setup();
        static void color(CRGB);
        static void animation_loop();
};

#endif