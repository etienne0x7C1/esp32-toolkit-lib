#include <WebSocketService.h>
#include <string>
AsyncWebSocket WebSocketService::aws("/ws");
std::vector<WebSocketService *> *WebSocketService::instances = new std::vector<WebSocketService *>();

// Allocate the JSON document
//
// Inside the brackets, 200 is the capacity of the memory pool in bytes.
// Don't forget to change this value to match your JSON document.
// Use arduinojson.org/v6/assistant to compute the capacity.
// StaticJsonDocument<200> doc;

// StaticJsonDocument<N> allocates memory on the stack, it can be
// replaced by DynamicJsonDocument which allocates in the heap.
//
// DynamicJsonDocument doc(200);
StaticJsonDocument<200> WebSocketService::jsonMsg;

// JSON stub string.
//
// Using a char[], as shown here, enables the "zero-copy" mode. This mode uses
// the minimal amount of memory because the JsonDocument stores pointers to
// the input buffer.
// If you use another type of input, ArduinoJson must copy the strings from
// the input to the JsonDocument, so you need to increase the capacity of the
// JsonDocument.
char jsonDataStub[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

WebSocketService::WebSocketService(std::string name) : name(name)
{
    // register service instance
    WebSocketService::instances->push_back(this);
}

void WebSocketService::dispatch(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {
        data[len] = 0;
        // convert raw data input
        std::string clientMsg(data, data + len);
        std::string serverMsg("");

        // convert to a json object
        DeserializationError error = deserializeJson(jsonMsg, clientMsg);

        // Test if parsing succeeds.
        if (!error)
        {
            // JsonObject jsonObj = jsonMsg.as<JsonObject>();

            // for (JsonPair kv : jsonObj)
            // {
            //     std::string serviceName(kv.key().c_str());
            //     JsonObject serviceData = kv.value().as<JsonObject>();

            // }
            // dispatch message to corresponding service
            std::string serviceName = jsonMsg["service"];
            Serial.println(serviceName.c_str());
            for (auto service : *WebSocketService::instances)
            {
                Serial.println(service->name.c_str());
                // match service name
                if (service->name.compare(serviceName) == 0)
                {
                    std::string log = "[WebSocket] message routed to service " + serviceName;
                    Serial.println(log.c_str());
                    service->process();
                }
            }

            serverMsg.append(clientMsg);
        }
        else
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
        }

        // notify server response to all clients
        String dataOut(serverMsg.c_str());
        aws.textAll(dataOut);
    }
}

void WebSocketService::eventHandler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
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
        Serial.println("[WebSocket] Data received");
        dispatch(arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}

void WebSocketService::process()
{
    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do doc["time"].as<long>();
    const char *sensor = jsonMsg["sensor"];
    long time = jsonMsg["time"];
    double latitude = jsonMsg["data"][0];
    double longitude = jsonMsg["data"][1];

    // Print values.
    Serial.println(sensor);
    Serial.println(time);
    Serial.println(latitude, 6);
    Serial.println(longitude, 6);
}