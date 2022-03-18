# esp32-toolkit-lib
ESP32 firmware building lib

## Purpose

Aim is to provide a set of useful features commonly used in ESP32 firmware development,
As well as a flexible architecture to develop custom firmware modules. 

Several other benefits among which:
- no boilerplate code
- entirely automated build process
- ready to use workspace dev environment
- easy to maintain and evolve 

## Key features:
- based upon latest arduino-esp32 framework (v2): mandatory to use littleFS and not available to date in PIO
- `littleFS` filesystem with strong advantage (over SPIFFS) to support directories. 

## Predefined firmwares
Aset of predefined firmwares is ready to be used:

- mini version
- base version: mini version + network + filesys + web server + web sockets + OTA
- full version: base version + json + 
