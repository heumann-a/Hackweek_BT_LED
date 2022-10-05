// Verknüpfung der Programmierbarendateien miteinander, damit diese zusammenarbeiten können
#include <string.h>
#include "bluetooth.h"
#include "config.h"
#include "led.h"


/* Prueft ob die Bluetooth Konfiguration im Projekt aktiviert ist */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/**
 * @brief Initialisierung des Bluetooth Modul
 */
void Blt::setup() {

    Blt::SerialBT.begin(BT_DEVICENAME);
    Serial.println("Bluetooth Started! Ready to pair...");
}

/**
 * @brief Verarbeitet den naechsten Befehl und aktualisiert ggf. den Modus
 * @param [in] value Der Input als String
 */
void Blt::next_command(std::string &value) {

  // Befehl zur Behebung fehlerhafter Formatierungen, wenn ein Fehler vorliegt 
  if (!value.empty() && value.back() == '\n') {
    value.pop_back();
    // Pruefen auf alternative Formatierung und ggf. auch Entfernung
    if (value.back() == '\r')
      value.pop_back();
  }
  // Informationsausgabe für eine einfachere Fehlersuche während der Laufzeit
  if (value.length() > 0)
  {
    Serial.print("[New value] ");
    for (int i = 0; i < value.length(); i++)
    {
      Serial.print(value[i]);
    }
    Serial.println();
  }

  // Schleife zum Vergleichen der LED Modi (AN = led_on) und (AUS = led_off)
  if (value.compare("led_on") == 0) 
    Led::display_mode = 1;
  else if (value.compare("led_off") == 0)
    Led::display_mode = 0;

  //Else-if Statements zum aendern der Fabe von den LEDs
  else if (value.compare(BEFEHL_FARBE_BLAU) == 0) 
    Led::basis_farbe = CRGB::Aquamarine;
  else if (value.compare(BEFEHL_FARBE_ROT) == 0)
    Led::basis_farbe = CRGB::DarkRed;
  else if (value.compare(BEFEHL_FARBE_GRUEN) == 0) 
    Led::basis_farbe = CRGB::DarkGreen;
  else if (value.compare(BEFEHL_FARBE_GELB) == 0) 
    Led::basis_farbe = CRGB::Yellow;
  else if (value.compare(BEFEHL_FARBE_VIOLET) == 0) 
    Led::basis_farbe = CRGB::DarkViolet;
  else if (value.compare(BEFEHL_FARBE_ROSA) == 0) 
    Led::basis_farbe = CRGB::MistyRose;

  // Else-if Statements zum aendern des Modus der LEDs
  else if (value.compare(BEFEHL_MODUS_1) == 0)
    Led::display_mode = 1;
  else if (value.compare(BEFEHL_MODUS_1) == 0)
    Led::display_mode = 2;
  else if (value.compare(BEFEHL_MODUS_1) == 0)
    Led::display_mode = 3;
  else if (value.compare(BEFEHL_MODUS_1) == 0)
    Led::display_mode = 4;
}

/**
 * @brief Schleife vom Bluetooth zum Lesen neuer Befehle und Weitergabe der Befehle
 */
void Blt::loop() {
  char input[50] = {};
  uint8_t index = 0;

  while (Blt::SerialBT.available() && index < 50)
  {
      input[index++]= Blt::SerialBT.read();
  }
  
  // Check-Methode, ob die neuen Daten ausgelesen wurden
  if (index >= 1) {
    std::string str(input);
    Blt::next_command(str);
  }

}

BluetoothSerial Blt::SerialBT;