// Klasse des Bluetooth-Gerätes
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "BluetoothSerial.h"

class Blt {

    private:
        static BluetoothSerial SerialBT;

    public:
        static void next_command(char *, uint8_t );
        static void setup();
        static void loop();
};


#endif