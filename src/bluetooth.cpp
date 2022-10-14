// Verknüpfung der Programmierbarendateien miteinander, damit diese zusammenarbeiten können
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
void Blt::next_command(char* value, uint8_t length) {

  // Befehl zur Behebung fehlerhafter Formatierungen, wenn ein Fehler vorliegt 
  if(value[length -1] == '\n') {
    value[length -1] = 0;
    --length;
    // Pruefen auf alternative Formatierung und ggf. auch Entfernung
    if (value[length -1] == '\r') {
      value[length -1] = 0;
      --length;
    }
  }
  
  // Informationsausgabe für eine einfachere Fehlersuche während der Laufzeit
  if (length > 0)
  {
    Serial.print("[New value] ");
    for (int i = 0; i < length; i++)
    {
      Serial.print(value[i]);
    }
    Serial.println();
  }

  // Schleife zum Vergleichen der LED Modi (AN = led_on) und (AUS = led_off)
  if (strcmp(value,BEFEHL_AN) == 0) 
    Led::display_mode = 1;
  else if (strcmp(value, BEFEHL_AUS) == 0)
    Led::display_mode = 0;

  uint8_t helligkeit = BRIGTHNESS;
  if(value[0]== '%'){
    //Pruefe ob die nachfolgenden Zeichen alles Zahlen sind
    helligkeit = atoi(value + 1);
    // Wenn außerhalb Wertebereich, zurücksetzen auf standardwert
    if( !(helligkeit >= 0 && helligkeit <= 255))
      helligkeit = BRIGTHNESS;
    FastLED.setBrightness(helligkeit);
  }

  //Else-if Statements zum aendern der Fabe von den LEDs
  else if (strcmp(value,BEFEHL_FARBE_BLAU) == 0) {
    Led::basis_farbe = CRGB::Aquamarine;
    return;
  }
  else if (strcmp(value,BEFEHL_FARBE_ROT) == 0) {
    Led::basis_farbe = CRGB::DarkRed;
    return;
  }
  else if (strcmp(value,BEFEHL_FARBE_GRUEN) == 0) {
    Led::basis_farbe = CRGB::DarkGreen;
    return;
  }
  else if (strcmp(value,BEFEHL_FARBE_GELB) == 0) {
    Led::basis_farbe = CRGB::Yellow;
    return;
  }
  else if (strcmp(value,BEFEHL_FARBE_VIOLET) == 0) {
    Led::basis_farbe = CRGB::DarkViolet;
    return;
  }
  else if (strcmp(value,BEFEHL_FARBE_ROSA) == 0) {
    Led::basis_farbe = CRGB::MistyRose;
    return;
  }

  // Else-if Statements zum aendern des Modus der LEDs
  else if (strcmp(value,BEFEHL_MODUS_1) == 0) {
    Led::display_mode = 1;
    return;
  }
  else if (strcmp(value,BEFEHL_MODUS_2) == 0) {
    Led::display_mode = 2;
    return;
  }
  else if (strcmp(value,BEFEHL_MODUS_3) == 0) {
    Led::display_mode = 3;
    return;
  }
  else if (strcmp(value,BEFEHL_MODUS_4) == 0) {
    Led::display_mode = 4;
    return;
  }
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
    Blt::next_command(input, index);
  }

}

BluetoothSerial Blt::SerialBT;