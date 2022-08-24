// Global Imports 
#include "config.h"
#include "led.h"
// #include "bluetooth_le.h"
#include "bluetooth.h"

/*---------------------------------
  Author: Alex
  Date: 08/2022
-----------------------------------*/



// -------------------------------
//    SETUP the LED and Bluetooth
// -------------------------------
void setup() {
  // Setup Debug Info and wait to get all Infos
  Serial.begin(9600);
  delay(500);
  Serial.println();
  Serial.println("Starting up...");

  Blt::setup();
  Led::setup();
}

// -------------------------------
//    Loop for updating and animation
// -------------------------------
void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Test");
  delay(2000);


}

