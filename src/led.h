#ifndef LED_H
#define LED_H

#include <FastLED.h>
#include "config.h"


class Led {
    
    private:
        static bool active;

    public:
        static CRGB ids[];
        
        static void setup();
        static void set_activity(bool);
        static void fire();
};

#endif