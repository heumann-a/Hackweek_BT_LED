// Projekt Imports
#include "config.h"
#include "led.h"
#include "bluetooth.h"

/*---------------------------------
  Author: Alex
  Date: 08/2022
-----------------------------------*/



// -------------------------------
//    INITIALISIEREN von LED-Streifen und Bluetooth
// -------------------------------
void setup() {
  // Initialisieren der Kommunikation
  Serial.begin(9600);
  delay(500);
  Serial.println("Starting up...");

  // Funktion für Bluetooth
  Blt::setup();
  // Funktion für LED-Streifen
  Led::setup();
}

// -------------------------------
//    DAUERSCHLEIFE fuer Logik
// -------------------------------
void loop() {
  Blt::loop();
  Led::animation_loop();
}

