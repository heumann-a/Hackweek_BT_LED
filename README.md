# DIY LED Panel

Projektbeschreibung:
In diesem Projekt wurde mit einem ESP32 Mikrocontroller, LED Streifen und einem Bilderrahmen eine durch Bluetooth steuerbare Lampe erstellt.

// Datenstruktur des LED Panel Projekts der CodeWeek


## LED Panel
* [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
* [FastLED](https://github.com/FastLED/FastLED)
* [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino)

## Installation
Es wird ein ESP32 Mikrocontroller oder vergleichbares benötigt, ein Mikro USB-Kabel.
- Ändere die LED Einstellung und Bluetooth Namen in `src/config.h`.
- Lade den Code mittels Platformio hoch und genieße!


# Funktionsweise
Die Lampe ist als Bluetooth-Gerät in der Nähe auffindbar. Der Standard-Name ist "LED-Lampe". Dort sind auch die Befehle zum Ändern der Farbe und Modi eingetragen. 
Einfach das Handy wie mit jedem anderen BT-Gerät koppeln und vorzugsweise mit einer Bluetooth-Terminal-App wie z.B. [Google](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal) oder [Apple](https://apps.apple.com/de/app/bluetooth-terminal/id1058693037), einfach die befehle hinschicken.


## Dateien

Wichtige Dateien für Programmierung der Lampenfunktionen inklusive der Bluetoothfunktion

* [bluetooth.cpp](.\src\bluetooth.cpp)
* [bluetooth.h](.\src\bluetooth.h)
* [config.h](.\src\config.h)
* [led.cpp](.\src\led.cpp)
* [led.h](.\src\led.h)
* [main.cpp](.\src\main.cpp)

https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html
