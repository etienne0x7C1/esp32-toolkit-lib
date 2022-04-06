#include <Arduino.h>
#include <FirmwareModule.h>
#include <WiFi.h>
#include <iostream>
// #include "../../../Dont-Commit-Me.h"
class NetworkModule : public FirmwareModule {

public:
  // if redefining constructor, call base class to register
  NetworkModule() : FirmwareModule("Network") { FirmwareModule::setup(); }

  void setup() {
    Serial.println("[Network - Setup] Begin");
    // wifiAP();
    wifiSTA();
    Serial.println("[Network - Setup] Done");
  }

  void wifiAP() {
    Serial.print("[Network - WifiAP] Setting AP (Access Point)...");
    std::string hotspotSSID = ConfigLoader::jsonConfig["hotspotSSID"];
    std::string hotspotPWD = ConfigLoader::jsonConfig["hotspotPWD"];
    WiFi.softAP(hotspotSSID.c_str(), hotspotPWD.c_str());
    std::cout << "Setup with IP " << WiFi.softAPIP() << std::endl;
  }

  void wifiSTA() {
    std::string wifiSSID = ConfigLoader::jsonConfig["wifiSSID"];
    std::string wifiPWD = ConfigLoader::jsonConfig["wifiPWD"];
    Serial.print("[Network - WifiSTA] Connecting to ");
    Serial.print(wifiSSID.c_str());
    WiFi.begin(wifiSSID.c_str(), wifiPWD.c_str());

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    std::cout
        << std::endl
        << "Connected with IP address: "; //<< WiFi.localIP() << std::endl;
    Serial.print("IP address:");
    Serial.println(WiFi.localIP());
  }
};
