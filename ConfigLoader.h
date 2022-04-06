#include <Arduino.h>
#include <ArduinoJson.h>
#include <FirmwareModule.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <iostream>
#include <string>
// #include "../../../Dont-Commit-Me.h"
/**
 *   Loading config at runtime from an external json file
 */
class ConfigLoader : public FirmwareModule {

public:
  static StaticJsonDocument<200> jsonConfig;
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
    String finalString = "";
    Serial.println("[LittleFS] File Content:");
    while (file.available()) {
      finalString += (char)file.read();
    }
    file.close();
    // convert to a json object
    DeserializationError error = deserializeJson(jsonConfig, finalString);

    // Test if parsing succeeds.
    if (!error) {
      //serializeJson(jsonConfig, Serial);

      Serial.println("[ConfigLoader] Done parsing configuration");

    } else {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }
  }
};

StaticJsonDocument<200> ConfigLoader::jsonConfig;
