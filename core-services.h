#include <ArduinoJson.h>
#include <AsyncElegantOTA.h>
#include <LittleFS.h>
#include <WebServices.h>

/**
 *   OTA Update Service
 */

template <int SERVER_PORT> class OTAServiceWrapper : WebService<SERVER_PORT> {
public:
  OTAServiceWrapper() : WebService<SERVER_PORT>() {
    std::cout << "[OTAServiceWrapper] instance running on port " << SERVER_PORT
              << std::endl;
  }

  void start() {
    WebService<SERVER_PORT>::start();
    Serial.println("[OTAServiceWrapper] Starting OTA Update service");
    AsyncElegantOTA.begin(&WebService<SERVER_PORT>::server);
    // state = true;
    Serial.println("[OTAServiceWrapper] Ok");
  }
};

/**
 * Static Server
 */

template <int SERVER_PORT> class StaticServer : WebService<SERVER_PORT> {
public:
  StaticServer() : WebService<SERVER_PORT>() {
    std::cout << "[StaticServer] listenning on port " << SERVER_PORT
              << std::endl;
  }

  void start() {
    // checking server state and launch if not running
    WebService<SERVER_PORT>::start();
    // load static routes
    loadRoutes();
    // state = true;
  }

  void loadRoutes() {
    std::cout << "[WebService:" << SERVER_PORT
              << "] Loading static server routes" << std::endl;
    // Route for root / web page
    WebService<SERVER_PORT>::server.on(
        "/", HTTP_GET, [](AsyncWebServerRequest *request) {
          request->send(LittleFS, "/index.html", "text/html", false);
        });

    WebService<SERVER_PORT>::server.serveStatic("/", LittleFS, "/");
  }
};

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

/**
 *  WS implementation with JSON support
 */
template <int SERVER_PORT, const char *SOCKET_PATH>
class JsonWebSocketService : WebSocketService<SERVER_PORT, SOCKET_PATH> {
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
  StaticJsonDocument<200> jsonMsg;

  std::string processMsg(std::string rawMsg) {
    // convert to a json object
    DeserializationError error = deserializeJson(jsonMsg, rawMsg);
    // Check parsing was successful.
    if (!error) {

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

      std::string replyMsg("default replay");
      return replyMsg;
    }
  }
};

/**
 *  WS implementation with JSON support
 */
template <int SERVER_PORT, const char *SOCKET_PATH>
class MultiJsonWebSocketService : WebSocketService<SERVER_PORT, SOCKET_PATH> {
  // Message container shared by instances
  static StaticJsonDocument<200> jsonObj;

  std::string processMsg(std::string rawMsg) {
    // parse json string
    DeserializationError error = deserializeJson(jsonObj, rawMsg);
    std::string allReplies;
    // Test if parsing succeeds.
    if (!error) {
      // JsonObject jsonObj = jsonMsg.as<JsonObject>();

      // for (JsonPair kv : jsonObj)
      // {
      //     std::string serviceName(kv.key().c_str());
      //     JsonObject serviceData = kv.value().as<JsonObject>();

      // }
      // dispatch message to corresponding service
      std::string serviceName = jsonObj["service"];
      Serial.println(serviceName.c_str());
      for (auto service : *WebSocketService<SERVER_PORT, SOCKET_PATH>::instances) {
        Serial.println(service->name.c_str());
        // match service name
        if (service->name.compare(serviceName) == 0) {
          std::string log =
              "[WebSocket] message routed to service " + serviceName;
          Serial.println(log.c_str());
        //   service->process();
        }
      }

      allReplies.append("TODO");
    } else {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }
    return allReplies;
  }
};