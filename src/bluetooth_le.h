#ifndef BLUETOOTH_LE_H
#define BLUETOOTH_LE_H

#include <NimBLEDevice.h>
#include "config.h"


class BLE {

    public:
        static BLEServer* server_ptr;

        static void setup();
};

#endif