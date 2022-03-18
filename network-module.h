#include <FirmwareModule.h>
#include <Arduino.h>
#include <WiFi.h>
#include <iostream>
// #include "../../../Dont-Commit-Me.h"
class NetworkModule : public FirmwareModule
{
    static const char *hotspotSSID;
    static const char *hotspotPWD;

    static const char *wifiSSID;
    static const char *wifiPWD;

public:
    // if redefining constructor, call base class to register
    NetworkModule() : FirmwareModule("Network") 
    {
        FirmwareModule::setup();
    }

    void setup()
    {
        Serial.println("[Network - Setup] Begin");
        // wifiAP();
        wifiSTA();
        Serial.println("[Network - Setup] Done");
    }

    void wifiAP()
    {
        Serial.print("[Network - WifiAP] Setting AP (Access Point)...");
        WiFi.softAP(NetworkModule::hotspotSSID, NetworkModule::hotspotPWD);
        std::cout << "Setup with IP " << WiFi.softAPIP() << std::endl;
    }

    void wifiSTA()
    {
        WiFi.begin(NetworkModule::wifiSSID, NetworkModule::wifiPWD);
        // std::cout << "Connecting to " << wifiSSID << " network";
        Serial.print("[Network - WifiSTA] Connecting to ");
        Serial.print(NetworkModule::wifiSSID);

        // Wait for connection
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        std::cout << std::endl
                  << "Connected with IP address: "; //<< WiFi.localIP() << std::endl;
        Serial.print("IP address:");
        Serial.println(WiFi.localIP());
    }
};

const char *NetworkModule::hotspotSSID = "ChangeMe";
const char *NetworkModule::hotspotPWD = "ChangeMe";
const char *NetworkModule::wifiSSID = "customSSID";
const char *NetworkModule::wifiPWD = "customPWD";
