#include <iostream>
#include <Arduino.h>
#include <FirmwareModule.h>
#include <network-module.h>
#include <filesys-module.h>
#include <web-module.h>
#include <websocket-example.h>
#include <module-template.h>

NetworkModule networkModule;
FilesysModule filesysModule;
WebModule webModule;
TemplateModule testModule;

/**
 * setup
 */
void setup()
{
    Serial.begin(115200);
    Serial.println("[ESP32] First log!");
    // AsyncWebSocket ws("/ws");// = new AsyncWebSocket(wsUrl.c_str());
    // // create and bind websocket event handler
    // WebSocketImpl wsh(&ws);
    // ws.onEvent(wsh.eventHandler);
    // webModule.addWebSocket(&ws);
    //  bind websocket event handler
    WebSocketTemplate::aws.onEvent(WebSocketTemplate::eventHandler);
    webModule.addWebSocket(&WebSocketTemplate::aws);
    // Init all modules
    FirmwareModule::setupAll();
}

/**
 * main loop
 */
void loop()
{
    WebSocketTemplate::aws.cleanupClients();
    // Refresh all modules
    FirmwareModule::loopAll();
}