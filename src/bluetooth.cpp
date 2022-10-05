#include <string.h>
#include "bluetooth.h"
#include "config.h"
#include "led.h"


/* Prueft ob Bluetooth konfiguration im Projekt aktiviert ist */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/**
 * @brief Initialisiert Bluetooth normal 
 */
void Blt::setup() {

    Blt::SerialBT.begin(BT_DEVICENAME);
    Serial.println("Bluetooth Started! Ready to pair...");
}

/**
 * @brief Verarbeteit den naechsten Befehl und aktualisiert ggf. den Modus
 * @param [in] value Der Input als String
 */
void Blt::next_command(std::string &value) {

  // Bei fehlerhaften Befehl wird Formatierung behoben 
  if (!value.empty() && value.back() == '\n') {
    value.pop_back();
    // Pruefen auf alternative Formatierung und ggf. auch Entfernung
    if (value.back() == '\r')
      value.pop_back();
  }

  // Zur Information bei der Fehlersuche
  if (value.length() > 0)
  {
    Serial.print("[New value] ");
    for (int i = 0; i < value.length(); i++)
    {
      Serial.print(value[i]);
    }
    Serial.println();
  }

  // Vergleich Befehl mit angegebenen Modi
  if (value.compare("led_on") == 0) 
    Led::display_mode = 1;
  else if (value.compare("led_off") == 0)
    Led::display_mode = 0;
  else if (value.compare("1") == 0) 
    Led::display_mode = 1;
  else if (value.compare("2") == 0)
    Led::display_mode = 2;
  else if (value.compare("3") == 0) 
    Led::display_mode = 3;
  else if (value.compare("4") == 0) 
    Led::display_mode = 4;
  else if (value.compare("5") == 0)
    Led::display_mode = 5;
  
}

/**
 * @brief Schleife vom Bluetooth zum Lesen neuer Befehle und Weitergabe
 */
void Blt::loop() {
  char input[50] = {};
  uint8_t index = 0;

  while (Blt::SerialBT.available() && index < 50)
  {
      input[index++]= Blt::SerialBT.read();
  }
  
  // Check if new Data was read
  if (index >= 1) {
    std::string str(input);
    Blt::next_command(str);
  }

}

BluetoothSerial Blt::SerialBT;