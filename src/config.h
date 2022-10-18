// Konfigurations Datei für den Code des ESP-Moduls
#ifndef LED_CONFIG_H
#define LED_CONFIG_H

// ===============
// DO NOT CHANGE
#define BLE_SERVICE_UUID    "ABCD"
#define BLE_CHAR_UUID       "1234"
// ===============

#define LED_CHIPSET WS2812B
#define LED_PORT    18
#define NUM_LEDS    15
#define BRIGTHNESS  20

#define BLE_MODUS           false
#define BT_DEVICENAME       "LED-Lampe"

#define BEFEHL_AN           "an"
#define BEFEHL_AUS          "aus"

#define BEFEHL_FARBE_BLAU   "blau"
#define BEFEHL_FARBE_ROT    "rot"
#define BEFEHL_FARBE_GRUEN  "gruen"
#define BEFEHL_FARBE_GELB   "gelb"
#define BEFEHL_FARBE_VIOLET "violet"
#define BEFEHL_FARBE_ROSA   "rosa"

#define BEFEHL_MODUS_1      "einfarbig"
#define BEFEHL_MODUS_2      "regenbogen"
#define BEFEHL_MODUS_3      "lauflicht"
#define BEFEHL_MODUS_4      "rampe"
#define BEFEHL_MODUS_5      "platzhalter"

#endif