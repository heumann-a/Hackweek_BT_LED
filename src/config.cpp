#include <LittleFS.h>
#include <ArduinoJson.h>

#include "config.h"

#define CFG_CURRENT_MODE "current_mode"
#define FILENAME "/led_config.json"

void Config::save() {
    File file = LittleFS.open(FILENAME, "w");

    if(!file) {
        Serial.println("Failed to open config file for writing.");
        return;
    }  

    StaticJsonDocument<256> doc;
    doc[CFG_CURRENT_MODE] = Config::current_mode;

}

void Config::load() {

    // Load Default Values
    Config::current_mode = 0;

    File file = LittleFS.open(FILENAME, "r");

    if(!file) {
        Serial.println("Failed to open config file.");
        Config::save();
        return;
    }

    StaticJsonDocument<1024> doc;
    deserializeJson(doc, file);

    Config::current_mode = doc[CFG_CURRENT_MODE].as<int>();
}

int Config::current_mode;