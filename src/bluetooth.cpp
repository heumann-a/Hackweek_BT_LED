// Verknüpfung der programmierbaren Dateien miteinander, damit diese zusammenarbeiten können
#include "bluetooth.h"
#include "config.h"
#include "led.h"



/* Prueft ob die Bluetooth Konfiguration im Projekt aktiviert ist */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif



/**
 * @brief Initialisiert Bluetooth normal oder als LE
 * @param [in] blt_active Aktiviert normales BLT wenn wahr.
 */
void Blt::setup() {

  if (BLE_MODUS) {
  // Bluetooth Low Energy (BLE)
    Serial.println("Startup BLE Server!");

    BLEDevice::init(BT_DEVICENAME);
    /** Optional: set the transmit power, default is 3db */
    NimBLEDevice::setPower(ESP_PWR_LVL_P9);

    Blt::pServer_BLE = NimBLEDevice::createServer();
    // Blt::pServer_BLE->setCallbacks(new ServerCallBack);

    NimBLEService *pService = Blt::pServer_BLE->createService(BLE_SERVICE_UUID);
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                          BLE_CHAR_UUID,
                                          NIMBLE_PROPERTY::READ |
                                          NIMBLE_PROPERTY::WRITE |
                                          NIMBLE_PROPERTY::BROADCAST |
                                          NIMBLE_PROPERTY::NOTIFY
                                          );

    pCharacteristic->setValue(BEFEHL_AUS);
    pCharacteristic->setCallbacks(&Blt::chrCallbacks);

    // Setup of BLE fertig, starte Alles
    pService->start();

    // Fuege die Dienste zum Advertisement hinzu um sie später verfügbar zu machen
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(BLE_SERVICE_UUID);

    // Ein Paar Einstellungen für iPhone etc.
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMaxPreferred(0x12);

    // Starte Advertisement
    pAdvertising->start();
  } else {
    // Serielles Bluetooth
    Blt::SerialBT.begin(BT_DEVICENAME);
    Serial.println("Bluetooth Started! Ready to pair...");
  }


 
}

/**
 * @brief Verarbeitet den naechsten Befehl und aktualisiert ggf. den Modus
 * @param [in] value Der Input als String
 */
void Blt::next_command(std::string &value) {

  // Wenn kein String übergeben wurde, brich ab
  if(value.empty())
    return;

  // Befehl zur Behebung fehlerhafter Formatierungen, wenn ein Fehler vorliegt 
  if(value.back() == '\n') {
      value.pop_back();
    // Pruefen auf alternative Formatierung und ggf. auch Entfernung
    if (value.back() == '\r') {
      value.pop_back();      
    }
  }

  // Informationsausgabe für eine einfachere Fehlersuche während der Laufzeit
  if (!value.empty()) {
    Serial.print("[EINGABE] - ");
    for (int i = 0; i < value.length(); i++)
    {
      Serial.print(value[i]);
    }
    Serial.println();
  }

  // -----------------------
  // An und Aus-schalten der LEDs
  // -----------------------
  if (value.compare(BEFEHL_AN) == 0) 
    Led::display_mode = 1;
  else if (value.compare(BEFEHL_AUS) == 0)
    Led::display_mode = 0;

  // -----------------------
  // Ändere die Helligkeit
  // -----------------------
  if(value[0]== '%'){
    unsigned int helligkeit = BRIGTHNESS;
    // Entferne das "%" Symbol an Stelle 0
    value.erase(0, 1);
    // Konvertiere die Zeichenfolge zu einer Zahl
    try {
      helligkeit = std::stoi(value, nullptr, 10);
      // Wenn Zahl größer 100, setze auf 100% zurück
      // Zahl kann nicht negativ werden, weil unsigned für nur positive Zahlen steht
      if (helligkeit > 100)
        helligkeit = 100;
      
      // Konvertiere von Prozent zu Wertebereich von 0-255
      helligkeit = (helligkeit * 255) / 100;

    } catch(const std::invalid_argument& e) {
      Serial.println("Konversion STR zu Integer aufgrund ungültiger Eingabe fehlgeschlagen!");
    } catch(const std::out_of_range& e) {
      Serial.println("Eingabe außerhalb Wertebereich!");
    }

    Led::change_brightness(helligkeit); 
  }

  // -----------------------
  //Else-if Statements zum aendern der Fabe von den LEDs
  // -----------------------
  else if (value.compare(BEFEHL_FARBE_BLAU) == 0) {
    Led::basis_farbe = CRGB::Aquamarine;
    return;
  }
  else if (value.compare(BEFEHL_FARBE_ROT) == 0) {
    Led::basis_farbe = CRGB::DarkRed;
    return;
  }
  else if (value.compare(BEFEHL_FARBE_GRUEN) == 0) {
    Led::basis_farbe = CRGB::DarkGreen;
    return;
  }
  else if (value.compare(BEFEHL_FARBE_GELB) == 0) {
    Led::basis_farbe = CRGB::Yellow;
    return;
  }
  else if (value.compare(BEFEHL_FARBE_VIOLET) == 0) {
    Led::basis_farbe = CRGB::DarkViolet;
    return;
  }
  else if (value.compare(BEFEHL_FARBE_ROSA) == 0) {
    Led::basis_farbe = CRGB::MistyRose;
    return;
  }

  // -----------------------
  // Else-if Statements zum aendern des Modus der LEDs
  // -----------------------
  else if (value.compare(BEFEHL_MODUS_1) == 0) {
    Led::display_mode = 1;
    return;
  }
  else if (value.compare(BEFEHL_MODUS_2) == 0) {
    Led::display_mode = 2;
    return;
  }
  else if (value.compare(BEFEHL_MODUS_3) == 0) {
    Led::display_mode = 3;
    return;
  }
  else if (value.compare(BEFEHL_MODUS_4) == 0) {
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
    std::string string_val(input);
    Blt::next_command(string_val);
  }

}

/**
 * @brief Initialize the BLE or BLT environment.
 * @param [in] blt_active Activates BLT if true.
 */
void CharacteristicCallbacks::onWrite(NimBLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    Blt::next_command(value);
}

void CharacteristicCallbacks::onRead(NimBLECharacteristic* pCharacteristic){
    Serial.print(pCharacteristic->getUUID().toString().c_str());
    Serial.print(": onRead(), value: ");
    Serial.println(pCharacteristic->getValue().c_str());
};

void CharacteristicCallbacks::onNotify(NimBLECharacteristic* pCharacteristic) {
    Serial.println("Sending notification to clients");
};

NimBLEServer* Blt::pServer_BLE;
BluetoothSerial Blt::SerialBT;
CharacteristicCallbacks Blt::chrCallbacks;