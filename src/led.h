#ifndef LED_H
#define LED_H

#include <FastLED.h>


class Led {
    
    private:
        static CRGB ids[];

        static void fire();
    public:
        
        static void setup();
        static void change_ambient(int);
};

#endif