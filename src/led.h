#ifndef LED_H
#define LED_H

#include <FastLED.h>


class Led {
    
    private:
        static CRGB ids[];

        static void fire();
        static void rainbow(uint8_t, uint8_t);
        static void lauflicht(u_int8_t);
        static void hoch_runter(u_int8_t);
    public:
        
        static int display_mode;
        static CRGB basis_farbe;
        static void setup();
        static void color(CRGB);
        static void animation_loop();
        static void change_brightness(uint8_t);
};

#endif