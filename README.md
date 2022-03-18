# esp32-toolkit-lib
ESP32 firmware building lib

## Purpose

Aim is to provide useful features commonly used in ESP32 firmware development and a flexible architecture to develop custom firmware modules. 

Several other benefits among which:
- no boilerplate code
- entirely automated build process
- ready to use workspace dev environment
- easy to maintain and evolve 

## Key features:
- latest [arduino-esp32](https://github.com/espressif/arduino-esp32) framework ([docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/)): mandatory to use littleFS (not available to date in PIO)
- `littleFS` filesystem with strong advantage (over SPIFFS) to support directories. 

## Predefined firmwares
A set of predefined firmwares is ready to be used:

- mini version
- base version: mini version + network + filesys + web server + web sockets + OTA
- full version: base version + json + 
