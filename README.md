# esp32-toolkit-lib
ESP32 firmware building lib

## Purpose

The aim of this lib is to provide a set of useful features commonly used in ESP32 firmware development,
as well as to provide a flexible architecture to develop custom firmware modules. 

There are also several other benefits such as:
- no boilerplate code
- entirely automatised build process
- ready to use workspace dev environment
- customizable and easy to evolve 

## Key features:
- based upon latest arduino-esp32 framework (v2): mandatory to use littleFS and not available to date in PIO
- `littleFS` filesystem with strong advantage (over SPIFFS) to support directories. 

## Predefined firmwares
It has a set of predefined firmwares ready to be used:

- mini version
- base version: mini version + network + filesys + web server + web sockets + OTA
- full version: base version + json + 