// Klasse des Bluetooth-Gerätes
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <NimBLEDevice.h>
#include <string.h>
#include "BluetoothSerial.h"



class CharacteristicCallbacks: public NimBLECharacteristicCallbacks {
    public:
        void onWrite(NimBLECharacteristic*);
        void onRead(NimBLECharacteristic*);
        void onNotify(NimBLECharacteristic*);
};

class Blt {

    private:
        static BluetoothSerial SerialBT;
        static NimBLEServer* pServer_BLE;

        static CharacteristicCallbacks chrCallbacks;
    public:
        static void next_command(std::string &);
        static void setup();
        static void loop();
};

#endif