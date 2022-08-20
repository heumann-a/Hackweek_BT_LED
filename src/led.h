#ifndef LED_H
#define LED_H

#include <FastLED.h>
#include "config.h"

class Led {
    
    public:
        static CRGB ids[];
        
        static void setup();
};

#endif