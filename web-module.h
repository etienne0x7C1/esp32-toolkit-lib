#include <FirmwareModule.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <server-routes.h>
// #include <websocket-impl.h>
// #include <ArduinoJson.h>
// #include <WebSocket.h>
// #include <web-controls.h>
/**
 * One server per module providing services on specific port: 
 * http server routes, web sockets, OTA service
 * 
 * WebServer<port>
 *  -> List of available server routes
 *  -> List of Websockets implemented
 *  -> OTA service
 */
class WebModule : public FirmwareModule
{
    AsyncWebServer *server; //@todo customize port from constructor
    // std::vector<AsyncWebSocket *> *webSockets;

public:
    WebModule(int serverPort = 80) : FirmwareModule("WebServer")
    {
        server = new AsyncWebServer(serverPort);
        // webSockets = new std::vector<AsyncWebSocket *>();
    }

    void loadServerRoutes()
    {
        Serial.println("[WebServer] loading server routes");
        // @todo provide routes as argument
        initServerRoutes(server);
        Serial.println("[WebServer] Done");
    }

    void addWebSocket(AsyncWebSocket *ws)
    {
        Serial.println("[WebServer] add web socket");
        // AsyncWebSocket ws(wsRoute);
        // // bind websocket event handler
        // ws.onEvent(eventHandler);
        // bind websocket to webserver
        server->addHandler(ws);
        // webSockets->push_back(&ws);
        Serial.println("[WebServer] Done");
    }

    void startOTAService()
    {
        Serial.println("[WebServer] Starting OTA Update service");
        AsyncElegantOTA.begin(server);
        Serial.println("[WebServer] Ok");
    }

    void setup()
    {
        // Serial.println("");
        // Loading services and routes
        loadServerRoutes();
        startOTAService();
        // @todo create and assign websockets externally
        // AsyncWebSocket ws("/ws");
        // addWebSocket("/ws");
        // Start server
        Serial.println("[WebServer] Starting Server");
        server->begin();
        Serial.println("[WebServer] running!");
    }

    void loop()
    {
        // for (auto ws : *webSockets)
        // {
        //     ws->cleanupClients();
        // }
    }
};