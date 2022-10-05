// Konfigurations Datei für den Code des ESP-Moduls
#ifndef LED_CONFIG_H
#define LED_CONFIG_H

#define LED_CHIPSET WS2812B
#define LED_PORT    18
#define NUM_LEDS    20
#define BRIGTHNESS  50

#define BT_DEVICENAME           "LED-Lampe"
#define BLE_SERVICE_UUID        "dead"
#define BLE_CHARACTERISTIC_UUID "beaf"


#define LED_CASE_OFF    0
#define LED_CASE_1      1
#define LED_CASE_2      2
#define LED_CASE_3      3
#define LED_CASE_4      4
#define LED_CASE_5      5
#define LED_CASE_6      6


#endif