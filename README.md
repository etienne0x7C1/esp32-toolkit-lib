# esp32-toolkit-lib
ESP32 firmware build lib

Aim is to provide core features to quickly develop ESP32 firmware for various diy projects, as well as a modular architecture to extend firmware's features . 

## Worspace setup

### Remote development

Projects configuration is included to work with Gitpod out of the box.

Prefix repo url with `gitpod.io/#` to launch full remote workspace already preconfigured

### Local development

- Grab a workspace artifact 
- Extract workspace which includes source and project configuration
- Inside workspace root dir, create following symlinks
```
    ln -s lib/esp32-toolkit-lib/.config/platformio.ini platformio.ini
    ln -s lib/esp32-toolkit-lib/.config/.gitmodules .gitmodules
    ln -s lib/esp32-toolkit-lib/.config/scripts/replace_fs.py replace_fs.py
    mkdir src && ln -s ../lib/esp32-toolkit-lib/examples/firmware-main.cpp src/main.cpp
```

## Usage
### First time usage

- If using local dev environment, you'll need an installation of platformIO available on the machine.

- Once workspace setup done with one of the previous method, customize wifi settings:

- Project is then built with:

```pio run -e esp32-latest```

`esp32-latest` being one of the build environment specified in `platformio.ini` file.

This will create firmware file in folder: `.pio/build/esp32-latest/firmware.bin`, 

- Upload firmware to the board using serial.

### Next steps
- if wifi settings were correctly setup at previous step, the board should be available on local network.

Access it in browser with the url: `http://<board IP>` which will show the dashboard interface with several menus.

To find the board IP it is automatically displayed over serial interface on each boot.

- from now on, it won't be necessary to use serial to update firmware, which can be uploaded directly to the board
using OTA updater available at: `http://<board IP>/update`

- A custom firmware available in examples, can be built by linking main.cpp to the chosen firmware source file.

## Key features and embedded libraries
The lib makes use of the following libs:
- latest [arduino-esp32](https://github.com/espressif/arduino-esp32) framework ([docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/)): mandatory to use littleFS (not available to date in PIO)
- `littleFS` filesystem with strong advantage (over SPIFFS) to support directories. 
- `ArduinoJson`: support for JSON

## Architecture

The firmware architecture is made of different modules and services.
A module inherits the `FirmwareModule` class and can overrides `setup`, `loop` methods to provide its own implementation.
In a similar way, a service provides a custom implementation of another service such as `WebSocketService`.


### Core modules
The firmware can embedd several core modules which implements main device features:

- network: provides wifi connectivity in both AP (Access Point) and STA (Client) modes
- filesystem: LittleFS
- webserver
- WebSockets Service
- OTA service

### Custom modules
On top of these core modules, firmware can be easily extended through custom modules to provide additional features (such as specific sensor support, ...).
To get included in the main update loop, a custom module inherits the `FirmwareModule` class.
As C++ allows multiple inheritance, it can also inherit a service to make use of it.

For instance a module requiring acceess to websockets, will inherit both `FirmwareModule` and `WebSocketService` which will forward 
received message to process them.

## Purpose of this project

- as less as boilerplate code possible
- fully automated build process
- ready to code workspace (available as build artifacts)
- easy to maintain and customize 