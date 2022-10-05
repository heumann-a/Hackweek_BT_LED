#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "BluetoothSerial.h"
#include <NimBLEDevice.h>

class Blt {

    private:
        static BluetoothSerial SerialBT;

    public:
        static void next_command(std::string &);
        static void setup();
        static void loop();
};


#endif