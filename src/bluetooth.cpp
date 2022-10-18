// Verknüpfung der Programmierbarendateien miteinander, damit diese zusammenarbeiten können
#include "bluetooth.h"
#include "config.h"
#include "led.h"



/* Prueft ob die Bluetooth Konfiguration im Projekt aktiviert ist */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/**
 * @brief Initialisiert Bluetooth normal oder als LE
 * @param [in] blt_active AKtiviert normales BLT wenn wahr.
 */
void Blt::setup(bool blt_active) {

    Blt::SerialBT.begin(BT_DEVICENAME);
    Serial.println("Bluetooth Started! Ready to pair...");
    // Blt::setup_ble();
}

/**
 * @brief Initialize the BLE or BLT environment.
 */
void Blt::setup_ble() {

  Serial.println("Startup BLE Server!");

  BLEDevice::init(BT_DEVICENAME);
  pServer_BLE = BLEDevice::createServer();
  BLEService *pService = pServer_BLE->createService(BLE_SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                        BLE_CHARACTERISTIC_UUID,
                                        NIMBLE_PROPERTY::READ |
                                        NIMBLE_PROPERTY::WRITE 
                                        );

  pCharacteristic->setValue("Hello World says Neil");
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLE_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMaxPreferred(0x12);
  
 * @brief Initialisierung des Bluetooth Modul
 */
void Blt::setup() {

    Blt::SerialBT.begin(BT_DEVICENAME);
    Serial.println("Bluetooth Started! Ready to pair...");
}

/**
 * @brief Initialize the BLE or BLT environment.
 * @param [in] blt_active Activates BLT if true.
 */
void Blt::next_command(std::string &value) {

  // Cleanup if Newline Endcoding is there
  if (!value.empty() && value.back() == '\n') {
    value.pop_back();
    // Check for Windows Encoding
    if (value.back() == '\r')
      value.pop_back();
  }
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


  if(value[0]== '%'){
    uint64_t helligkeit = BRIGTHNESS;
    char *end;
    //Pruefe ob die nachfolgenden Zeichen alles Zahlen sind
    helligkeit = strtol(value + 1, &end, 10);
    // Wenn außerhalb Wertebereich, zurücksetzen auf standardwert
    helligkeit = (helligkeit > 255) ? 255 : helligkeit;
    
    Led::change_brightness(helligkeit); 
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

/**
 * @brief Initialize the BLE or BLT environment.
 * @param [in] blt_active Activates BLT if true.
 */
class MyCallbacks: public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();
    Blt::next_command(value);
  }
};

NimBLEServer* Blt::pServer_BLE;
BluetoothSerial Blt::SerialBT;