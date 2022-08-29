#include <string.h>
#include "bluetooth.h"
#include "config.h"
#include "led.h"

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/**
 * @brief Initialize the %BLE environment.
 * @param [in] blt_active The device name of the device.
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

void Blt::loop() {
  char input[50];
  uint8_t index = 0;

  while (Blt::SerialBT.available() && index < 50)
  {
      input[index]= Blt::SerialBT.read();
      // ---- For Debug -----
      // Serial.write(input[index++]);;
  }

  if (strcmp (input, "led_on") == 0)
    Led::color(CRGB::White);
  if (strcmp (input, "led_off") == 0)
    Led::color(CRGB::Black);

  int next_mode = atoi(input);
  if (next_mode <= AVAILABLE_MODES)
    Led::change_ambient(next_mode);

}

class MyCallbacks: public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();
    int next_mode = 0;

    if (value.length() > 0)
    {
      Serial.println("*********");
      Serial.print("New value: ");
      for (int i = 0; i < value.length(); i++)
      {
        next_mode += (value[i] - 48) * pow10(i);
        Serial.print(value[i]);
      }
      Serial.println();
      Serial.println("*********");
    }

    if ( next_mode <= AVAILABLE_MODES)
        Led::change_ambient(next_mode);
  }
};

void Blt::setup_ble() {

  Serial.println("Startup BLE Server!");

  BLEDevice::init("LED-Lampe");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLE_SERVICE_UUID);
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


NimBLEServer* Blt::pServer_BLE;
BluetoothSerial Blt::SerialBT;