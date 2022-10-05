#include "led.h"
#include "config.h"


/**
 * @brief Initialisiert LED-Streifen mit spezifierten Infos aus der config
 */
void Led::setup() {

  FastLED.addLeds<LED_CHIPSET, LED_PORT, GRB>(Led::ids, 0, NUM_LEDS);
  // 0-255 value range for 0-100%
  FastLED.setBrightness(BRIGTHNESS);

  Led::color(CRGB::Blue);
  FastLED.show();
  delay(1000);
  Led::color(CRGB::Black);
  FastLED.show();
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
 * @brief Switch-Statement, das prueft welcher Modus aktuell genutzt wird. Führt dementsprechend die Funktion aus.
 */
void Led::animation_loop() {
  
  switch (Led::display_mode)
  {
    case LED_CASE_OFF:
      Led::color(CRGB::Black);
      break;

    case LED_CASE_1:
      Led::color(Led::basis_farbe);
      break;

    case LED_CASE_2:
      static uint8_t gHue = 0;
      Led::rainbow(gHue, 12);
      EVERY_N_MILLISECONDS( 20 ) { gHue++; }
      break;

    case LED_CASE_3:
      static uint8_t lauflicht_base = 0;
      Led::lauflicht(lauflicht_base);
      EVERY_N_MILLISECONDS( 100 ) { lauflicht_base = (++lauflicht_base) % NUM_LEDS; }
      break;

    case LED_CASE_4:
      static bool increment = true;
      static uint8_t hoehe = 0;
      Led::hoch_runter(hoehe);
      EVERY_N_MILLISECONDS( 100 ) { 
        if (increment){
          ++hoehe;
          if(hoehe == NUM_LEDS)
            increment = false;
        } else {
          --hoehe;
          if(hoehe == 0)
            increment = true;
        }
       }
      break;

    default:
      Led::color(CRGB::White);
      break;
  
  }

}

/**
 * @brief Generiert einen Regenbogeneffekt ueber den kompletten Streifen mittles HSV des Farbspektrums
 * @param [in] initialhue Nächste HSV Farbwert für die erste LED
 * @param [in] deltahue Abstufung der Farben mit Delta E (auch Delta Wert genannt, dies ist ein Maß für den empfundenen Farbabstand(die Farbdifferenz),
 *  mit diesem können Farben leichter durch Zahlen beschrieben werden) 
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

/**
 * @brief Lässt einen Punkt über die LED Leiste laufen.
 * @param [in] startindex Aktuelle LED die den Start des Punktes darstellt.
 */
void Led::lauflicht(uint8_t startindex) {

  const uint8_t spannweite = 2;
  for( int i = 0; i < NUM_LEDS; ++i) {
    Led::ids[i] = Led::basis_farbe;
    if( i >= startindex && i <= (startindex + spannweite))
      Led::ids[i] = CRGB::White;
  }
  FastLED.show();
}

/**
 * @brief (De)aktiviert die LEDS in der Reihe nach bis alle oder keins mehr leuchtet (Rampenmäßig)
 * @param [in] hoehe Aktueller Wert bis zu diesem die LED angeschalten werden
 */
void Led::hoch_runter(uint8_t hoehe) {

  for( int i = 0; i < NUM_LEDS; ++i) {
    if (i <= hoehe)
      Led::ids[i] = Led::basis_farbe;
    else  
      Led::ids[i] = CRGB::Black;
  }
  FastLED.show();
}

CRGB Led::ids[NUM_LEDS];
int Led::display_mode = 0;
CRGB Led::basis_farbe = CRGB::White;