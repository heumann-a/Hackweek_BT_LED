#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "BluetoothSerial.h"
#include <NimBLEDevice.h>

class Blt {

    private:
        static BLEServer* pServer_BLE;
        static BluetoothSerial SerialBT;

        static void setup_ble();

    public:
        static void next_command(std::string &);
        static void setup(bool);
        static void loop();
};


#endif