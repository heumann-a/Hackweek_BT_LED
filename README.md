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
  - `LED_PORT` ist zu entsprechend dem Datenkabel richtig einzutragen
  - `NUM_LEDS` sind die Anzahl an LEDs die verbaut sind
  - `BRIGHTNESS` ist die Standard Helligkeit und darf im Wertebereich von 0-255 liegen, dies entspricht 0-100%
  - Wird ein anderer LED-Streifen verwendet, muss dementsprechend auch `LED_CHIPSET` angepasst werden
- Lade den Code mittels Platformio hoch und genieße!


# Konfiguration
Die Lampe ist als Bluetooth-Gerät in der Nähe auffindbar. Der Standard-Name ist "LED-Lampe". Dort sind auch die Befehle zum Ändern der Farbe und Modi eingetragen. 
Einfach das Handy wie mit jedem anderen BT-Gerät koppeln und vorzugsweise mit einer Bluetooth-Terminal-App wie z.B. [Google](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal) oder [Apple](https://apps.apple.com/de/app/bluetooth-terminal/id1058693037), einfach die befehle hinschicken.


## Anpassung Bluetooth iOS

Aufgrund Bluetooth Limitierungen funktioniert entweder Bluetooth im seriellen Modus oder im LE Modus, jedoch nie beides gleichzeitig. Aus Erfahrungen mit iOS funktioniert Bluetooth im seriellen Modus nur mäßig gut, da dort die Gerätenamen nicht angezeigt werden. 
Für iPhone und iOS Nutzer ist deshalb der LE Modus zu empfehlen welcher in der  [config.h](.\src\config.h) durch setzen des *BLE_MODUS* auf **true** aktiviert werden kann

Des Weiteren sind auch in der [config.h](.\src\config.h), die ganzen Befehle und Farben zu finden mit denen sich die Lampe steuern lässt

