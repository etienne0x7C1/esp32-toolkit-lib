#include <WebSocketService.h>
#include <string>
AsyncWebSocket WebSocketService::aws("/ws");
std::vector<WebSocketService *> *WebSocketService::instances =
    new std::vector<WebSocketService *>();

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
StaticJsonDocument<200> WebSocketService::jsonReply;

// JSON stub string.
//
// Using a char[], as shown here, enables the "zero-copy" mode. This mode uses
// the minimal amount of memory because the JsonDocument stores pointers to
// the input buffer.
// If you use another type of input, ArduinoJson must copy the strings from
// the input to the JsonDocument, so you need to increase the capacity of the
// JsonDocument.
char jsonDataStub[] =
    "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

WebSocketService::WebSocketService(std::string name) : name(name) {
  // register service instance
  WebSocketService::instances->push_back(this);
}
/**
 * Find related service to dispatch received message
 */
void WebSocketService::dispatchService(std::string serviceId) {
  for (auto service : *WebSocketService::instances) {
    Serial.println(service->name.c_str());
    // match service name
    if (service->name.compare(serviceId) == 0) {
      std::string log = "[WebSocket] message routed to service " + serviceId;
      Serial.println(log.c_str());
      service->processMsg();
      // @TODO insert service reply
      std::string serviceReply("empty");
      jsonMsg["reply"] = serviceReply;
    }
  }
}

// void WebSocketService::addServiceReply(std::string service,
// DynamicJsonDocument serviceReply) {
//     // add reply to jsonReply
// }

/**
 * Extract messages from request and dispatch to corresponding services
 */
void WebSocketService::routeMessages(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len &&
      info->opcode == WS_TEXT) {
    data[len] = 0;
    // convert raw data input
    std::string clientMsg(data, data + len);
    std::string replyMsg("");

    // parse received message to json
    DeserializationError error = deserializeJson(jsonMsg, clientMsg);

    // Test if parsing succeeds.
    if (!error) {
      // JsonObject jsonObj = jsonMsg.as<JsonObject>();

      // for (JsonPair kv : jsonObj)
      // {
      //     std::string serviceName(kv.key().c_str());
      //     JsonObject serviceData = kv.value().as<JsonObject>();

      // }
      // dispatch message to corresponding service
      // @todo loop on services
      std::string service = jsonMsg["service"];
      dispatchService(service);

      // addServiceReply(service, serviceReply)
      std::string serviceReply = jsonMsg["reply"];
      replyMsg = serviceReply;
    } else {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }

    // notify server response to all clients
    aws.textAll(replyMsg.c_str());
  }
}

void WebSocketService::eventHandler(AsyncWebSocket *server,
                                    AsyncWebSocketClient *client,
                                    AwsEventType type, void *arg, uint8_t *data,
                                    size_t len) {
  switch (type) {
  case WS_EVT_CONNECT:
    Serial.printf("[WebSocket] client #%u connected from %s\n", client->id(),
                  client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("[WebSocket] client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
    Serial.println("[WebSocket] Data received");
    routeMessages(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}