#include "led.h"
#include "config.h"


/**
 * @brief Initialisiert LED-Streifen mit spezifierten Infos aus der Konfig
 */
void Led::setup() {

  FastLED.addLeds<LED_CHIPSET, LED_PORT, GRB>(Led::ids, 0, NUM_LEDS);
  // 0-255 value range for 0-100%
  FastLED.setBrightness(BRIGTHNESS);

  Led::color(CRGB::Blue);
  delay(300);
  Led::color(CRGB::Black);
}

/**
 * @brief Färbt alle LEDs mit der spezifizierten Farbe
 * @param [in] CRGB Neue Farbe
 */
void Led::color(CRGB new_color) {
  for(int i = 0; i < NUM_LEDS; i++) {
      Led::ids[i] = new_color;
  }
  FastLED.show();
}

/**
 * @brief Schleife, die prueft welcher Modus aktuell genutzt wird und führt dementsprechend die Funktion aus
 */
void Led::animation_loop() {

  switch (Led::display_mode)
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
      Led::color(CRGB::DarkGreen);
      break;

    case 4:
      Led::color(CRGB::Honeydew);
      break;

    case 5:
      static uint8_t gHue = 0;
      Led::rainbow(gHue, 12);
      EVERY_N_MILLISECONDS( 20 ) { gHue++; }
      break;

    default:
      Led::color(CRGB::White);
      break;
  
  }

}

/**
 * @brief Generiert einen Regenbogeneffekt ueber den kompletten Streifen mittles HSV farben
 * @param [in] initialhue Nächste HSV Farbwert für erste LED
 * @param [in] deltahue Abstufung der Farben mit Deltawert
 */
void Led::rainbow(uint8_t initialhue, uint8_t deltahue) {

  CHSV hsv;
  hsv.hue = initialhue;
  hsv.val = 255;
  hsv.sat = 240;
  for( int i = 0; i < NUM_LEDS; ++i) {
      Led::ids[i] = hsv;
      hsv.hue += deltahue;
  }
  FastLED.show();
}

CRGB Led::ids[NUM_LEDS];
int Led::display_mode = 0;