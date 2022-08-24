#include "bluetooth.h"
#include "config.h"


/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


void Blt::setup() {

  Blt::SerialBT.begin(BT_DEVICENAME);
  Serial.println("Bluetooth Started! Ready to pair...");
}

void Blt::loop() {
  if (Serial.available())
  {
    Blt::SerialBT.write(Serial.read());
  }
  if (Blt::SerialBT.available())
  {
    Serial.write(Blt::SerialBT.read());
  }
  delay(20);
}

BluetoothSerial Blt::SerialBT;