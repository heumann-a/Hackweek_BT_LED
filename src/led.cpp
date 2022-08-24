#include "led.h"
#include "config.h"

void Led::setup() {

    FastLED.addLeds<LED_CHIPSET, LED_PORT, GRB>(Led::ids, 0, NUM_LEDS);
    // 0-255 value range for 0-100%
    FastLED.setBrightness(10);

    for(int i = 0; i < NUM_LEDS; i++) {
        Led::ids[i].setRGB(0, 0, 0);
    }

    FastLED.show();
}

void Led::set_activity(bool val) {
    Led::active = val;
}


#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120
void Led::fire() {
    static uint8_t heat[NUM_LEDS];
    bool gReverseDirection = false;

    // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      Led::ids[pixelnumber] = color;
    }
}

CRGB Led::ids[NUM_LEDS];
bool Led::active = false;