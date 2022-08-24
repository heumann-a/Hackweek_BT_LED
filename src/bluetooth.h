#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "BluetoothSerial.h"

class Blt {

    private:
    
        static BluetoothSerial SerialBT;
    
    public:

        static void setup();
        static void loop();
};

#endif