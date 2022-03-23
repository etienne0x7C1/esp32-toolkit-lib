# esp32-toolkit-lib
ESP32 firmware build lib

Aim is to provide core features to quickly develop ESP32 firmware for various diy projects, as well as a modular architecture to extend firmware's features . 

# Quick start

- Grab a workspace artifact which includes source and project configuration
- Customize wifi settings in `network-module.h`.
- Build one of the default firmware available in exemples by linking main.cpp to the chosen firmware source file.
- Upload to the board using serial interface.


## Included frameworks, librairies
The lib makes use of the following libs:
- latest [arduino-esp32](https://github.com/espressif/arduino-esp32) framework ([docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/)): mandatory to use littleFS (not available to date in PIO)
- `littleFS` filesystem with strong advantage (over SPIFFS) to support directories. 
- `ArduinoJson`: provide support for JSON

# Architecture

The firmware architecture is made of different modules and services.
A module inherits the `FirmwareModule` class and can overrides `setup`, `loop` methods to provide its own implementation.
In a similar way, a service provides a custom implementation of another service such as `WebSocketService`.


## Core modules
The firmware can embedd several core modules which implements main device features:

- network: provides wifi connectivity in both AP (Access Point) and STA (Client) modes
- filesystem: LittleFS
- webserver
- WebSockets Service
- OTA service

## Custom modules
On top of these core modules, firmware can be easily extended through custom modules to provide additional features (such as specific sensor support, ...).
To get included in the main update loop, a custom module inherits the `FirmwareModule` class.
As C++ allows multiple inheritance, it can also inherit a service to make use of it.

For instance a module requiring acceess to websockets, will inherit both `FirmwareModule` and `WebSocketService` which will forward 
received message to process them.

# Purpose of this project

- as less as boilerplate code possible
- fully automated build process
- ready to code workspace (available as build artifacts)
- easy to maintain and customize 