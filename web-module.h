#include <FirmwareModule.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
// #include <WebSocket.h>
// #include <server-routes.h>
// #include <web-controls.h>
#include <iostream>

class WebModule : public FirmwareModule
{
    static AsyncWebServer server;
    static AsyncWebSocket ws;

public:
    WebModule() : FirmwareModule("Web")
    {
    }

    void setup()
    {
        // WebSocketServerImpl::ws = &ws;
        // bind websocket event handler
        // ws.onEvent(WebSocketServerImpl::eventHandler);
        // bind websocket to webserver
        server.addHandler(&ws);
        // initServerRoutes(&server);
        // Serial.println("OK");
        // Serial.println("");

        Serial.println("[Web - OTA Updater]");
        AsyncElegantOTA.begin(&server);
        Serial.println("OK");
        Serial.println("");

        // Start server
        server.begin();
    }

    void loop()
    {
        WebModule::ws.cleanupClients();
    }
};

AsyncWebServer WebModule::server(80);
AsyncWebSocket WebModule::ws("/ws");