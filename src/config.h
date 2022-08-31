#ifndef LED_CONFIG_H
#define LED_CONFIG_H

#define LED_CHIPSET WS2812B
#define LED_PORT    15
#define NUM_LEDS    20
#define BRIGTHNESS  50

#define BT_DEVICENAME           "LED-Lampe"
#define BLE_SERVICE_UUID        "dead"
#define BLE_CHARACTERISTIC_UUID "beaf"

class Config {

    public:
        static int current_mode;

        static void load();
        static void save();
};

#endif