#include <FirmwareModule.h>
#include <ESPAsyncWebServer.h>
#include <string>

class WebSocketTemplate : public FirmwareModule
{
public:
    static AsyncWebSocket aws;

    // WebSocketImpl(string awsUrl) : FirmwareModule("WebSocket")
    // {
    //     Serial.printf("[WebSocket] creation");
    //     aws = new AsyncWebSocket(awsUrl.c_str());
    // }

    static void processClientMessage(void *arg, uint8_t *data, size_t len)
    {
        Serial.printf("[WebSocket] processClientMessage");

        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
        {
            data[len] = 0;
            // convert raw data input
            std::string dataIn(data, data + len);
            // do some process
            String dataOut(dataIn.c_str());
            // notify server response to all clients
            aws.textAll(dataOut);
        }
    }

    static void eventHandler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                      void *arg, uint8_t *data, size_t len)
    {
        switch (type)
        {
        case WS_EVT_CONNECT:
            Serial.printf("[WebSocket] client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("[WebSocket] client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
            Serial.printf("[WebSocket] Data received");
            processClientMessage(arg, data, len);
            break;
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
        }
    }

};

AsyncWebSocket WebSocketTemplate::aws("/ws");

// static void parseInput(String dataIn);

// Server response to clients
// @return: a jsonified string
// static String serverOutput()
// {
//     // std::string jsonString = "a jsonified string";
//     JSONVar jsarr;
//     jsarr["root"]["child"] = String("childValue");
//     String jsonStringOut = JSON.stringify(jsarr);
//     return jsonStringOut; //sJsonOutput;