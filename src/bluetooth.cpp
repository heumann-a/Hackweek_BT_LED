#include <string.h>
#include "bluetooth.h"
#include "config.h"
#include "led.h"


/* Prueft ob Bluetooth konfiguration im Projekt aktiviert ist */
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

  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
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

  // For Debugging Purpose
  if (value.length() > 0)
  {
    Serial.print("[New value] ");
    for (int i = 0; i < value.length(); i++)
    {
      Serial.print(value[i]);
    }
    Serial.println();
  }

  if (value.compare("led_on") == 0) 
    // Led::display_mode = Config::current_mode;
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
 * @brief Initialize the BLE or BLT environment.
 * @param [in] blt_active Activates BLT if true.
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