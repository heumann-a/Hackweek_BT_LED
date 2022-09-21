#include "led.h"
#include "config.h"

void Led::setup() {

  FastLED.addLeds<LED_CHIPSET, LED_PORT, GRB>(Led::ids, 0, NUM_LEDS);
  // 0-255 value range for 0-100%
  FastLED.setBrightness(BRIGTHNESS);

  Led::color(CRGB::Blue);
  delay(300);
  Led::color(CRGB::Black);
}

void Led::color(CRGB new_color) {
  for(int i = 0; i < NUM_LEDS; i++) {
      Led::ids[i] = new_color;
  }
  FastLED.show();
}

void Led::animation_color(int status) {

  switch (status)
  {
    case 0:
      Led::color(CRGB::Black);
      break;

    case 1:
      Led::color(CRGB::Aquamarine);
      break;

    case 2:
      Led::color(CRGB::DarkRed);
      break;
    
    case 3:
      
      break;

    case 4:
      static uint8_t gHue = 0;
      Led::rainbow(gHue, 7);
      EVERY_N_MILLISECONDS( 20 ) { gHue++; }
      break;

    case 5:
      Led::fire();
      break;

    default:
      Led::color(CRGB::White);
      break;
  
  }

}


void Led::rainbow(uint8_t initialhue, uint8_t deltahue) {

  CHSV hsv;
  hsv.hue = initialhue;
  hsv.val = 255;
  hsv.sat = 240;
  for( int i = 0; i < NUM_LEDS; ++i) {
      Led::ids[i] = hsv;
      hsv.hue += deltahue;
  }
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
int Led::display_mode = 0;