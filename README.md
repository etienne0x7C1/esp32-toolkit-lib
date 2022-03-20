# esp32-toolkit-lib
ESP32 firmware building lib

## Purpose

Aim is to provide useful features commonly used in ESP32 firmware development and a flexible architecture to develop custom firmware modules. 

Several other benefits among which:
- no boilerplate code
- fully automated build process
- ready to code workspace (available as build artifacts)
- easy to maintain and customize 

## Key features:
- latest [arduino-esp32](https://github.com/espressif/arduino-esp32) framework ([docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/)): mandatory to use littleFS (not available to date in PIO)
- `littleFS` filesystem with strong advantage (over SPIFFS) to support directories. 

## Predefined firmwares and build env
A set of predefined firmwares version is ready to be used:

- `firmware-mini`: no deps
- `firmware-base`: `firmware-mini` + network + filesys + web server + web sockets + OTA
- `firmware-cust`: `firmware-base` + json + ...
- `firmware-full`: `firmware-base` + ...

Customized PIO build environments:
- `legacy`
- `latest`: using latest `arduino-esp32` (v2)
