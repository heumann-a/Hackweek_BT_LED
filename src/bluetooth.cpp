#include <string.h>
#include "bluetooth.h"
#include "config.h"
#include "led.h"

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/**
 * @brief Initialize the BLE or BLT environment.
 * @param [in] blt_active Activates BLT if true.
 */
/* STATIC */
void Blt::setup(bool blt_active) {
    if ( blt_active )
        Blt::setup_blt();
    else
        Blt::setup_ble();
}

void Blt::setup_blt() {

  Blt::SerialBT.begin(BT_DEVICENAME);
  Serial.println("Bluetooth Started! Ready to pair...");
}


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

void Blt::next_command(std::string &value) {

  // Cleanup if Newline Endcoding
  if (!value.empty() && value.back() == '\n') {
    value.pop_back();
    // Check for Windows Encoding
    if (value.back() == '\r')
      value.pop_back();
}
  // For Debugging Purpose
  if (value.length() > 0)
  {
    Serial.println("*********");
    Serial.print("New value: ");
    for (int i = 0; i < value.length(); i++)
    {
      Serial.print(value[i]);
    }
    Serial.println();
    Serial.println("*********");
  }

  if (value.compare("led_on") == 0) 
    Led::change_ambient(Config::current_mode);

  if (value.compare("led_off") == 0)
    Led::change_ambient(0);

  if (value.compare("1") == 0) 
    Config::current_mode = 1;

  if (value.compare("2") == 0)
    Config::current_mode = 2;

  if (value.compare("3") == 0) 
    Config::current_mode = 3;

  if (value.compare("4") == 0) 
    Config::current_mode = 4;

  if (value.compare("5") == 0)
    Config::current_mode = 5;
  
  Led::change_ambient(Config::current_mode);
  Config::save();
}

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