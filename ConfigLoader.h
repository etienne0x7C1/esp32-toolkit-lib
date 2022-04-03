#include <Arduino.h>
#include <FirmwareModule.h>
#include <WiFi.h>
#include <iostream>
#include <LittleFS.h>
// #include "../../../Dont-Commit-Me.h"
/**
 *   Loading config at runtime from an external json file
 */
class ConfigLoader : public FirmwareModule {
  static const char *hotspotSSID;
  static const char *hotspotPWD;

  static const char *wifiSSID;
  static const char *wifiPWD;

public:
  // if redefining constructor, call base class to register
  ConfigLoader() : FirmwareModule("ConfigLoader") { FirmwareModule::setup(); }

  /**
   *   Load config from external file stored on device FS
   */
  void setup() {
    Serial.println("[ConfigLoader] loading");

    File file = LittleFS.open("/config.json", "r");
    if (!file) {
      Serial.println("[LittleFS] Failed to open config file");
      return;
    }

    Serial.println("[LittleFS] File Content:");
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();

    Serial.println("[ConfigLoader] Done");
    
  }
};
