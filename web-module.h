#include <FirmwareModule.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <server-routes.h>
// #include <WebSocket.h>
// #include <web-controls.h>

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
        Serial.println("[Web - Server] loading server routes");
        initServerRoutes(&server);
        Serial.println("[Web - Server] Done");
        // Serial.println("");

        Serial.println("[Web - OTA] Begin serving");
        AsyncElegantOTA.begin(&server);
        Serial.println("[Web - OTA] Ok");
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