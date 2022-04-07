# esp32-toolkit-lib
ESP32 firmware build lib

Aim is to provide core features to quickly develop ESP32 firmware for various diy projects, as well as a modular architecture to extend firmware's features . 

## Workspace setup

### Remote development

Gitpod workspace is meant to work out of the box pre-configuration and tools already installed.

Just prefix this repository url with `gitpod.io/#` to launch a fully configured remote workspace.

### Local development

- Download workspace artifact 
- Extract workspace which includes source and project configuration
- Inside workspace root dir, create following symlinks. 
one liner: 
``` 
ln -s lib/esp32-toolkit-lib/.config/platformio.ini platformio.ini && \
ln -s lib/esp32-toolkit-lib/.config/scripts/replace_fs.py replace_fs.py && \
ln -s lib/esp32-toolkit-lib/.config/.gitmodules .gitmodules && \
mkdir src/ && ln -s ../lib/esp32-toolkit-lib/examples/firmware-main.cpp src/main.cpp 
```

An installation of platformIO is required.

Using python package installer `pip` :

```
    python -m pip install --upgrade pip
    pip install --upgrade platformio
```

### Wifi configuration

before uploading firmware and filesystem images, wifi settings must be customized in `data/config.json` file

```
{
    "wifiSSID": "changeme",
    "wifiPWD": "changeme"
}
```

## Build

### firmware

``` pio run -e esp32-latest ```

resulting build file located at `.pio/build/esp32-latest/firmware.bin`

### filesystem image

``` pio run -t buildfs -e esp32-latest ```

resulting image file located at `.pio/build/esp32-latest/spiffs.bin`

## Upload
First time, device must be updated manually using serial upload, then it can be updated directly using OTA method.
### Serial
Upload 2 previous image files (`firmware.bin` and `spiffs.bin`) to the board.

- firmware:
``` pio run -e esp32-latest -t upload ```
- filesystem image:
```pio run -e esp32-latest -t uploadfs ```
### OTA
If wifi settings were correctly set in `config.json` file, device can be updated directly using Web updater available at: `http://<board IP>/update`

(device ip address is automatically displayed over serial interface on each boot).

In web interface, select either `firmware` and `firmware.bin` file to update firmware, or `filesystem` and `spiffs.bin` image file to update filesystem,

## Device Monitoring

Serial monitoring can be done from console:

`cat /dev/ttyUSB0`

make sure your user has access to serial interface by adding him to the correct group.

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

- ready to code workspace (available as build artifacts)
- as less as boilerplate code possible
- fully automated build process
- easy to maintain and customize 