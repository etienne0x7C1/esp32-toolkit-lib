#include "WebSocketService.h"

/**
* Perform GPIO operation remotely
*/
class GpioService : WebSocketService {

public:
//   static std::vector<GpioService *> *instances;              // the registered components to gpio service
//   std::vector<int> *pinConfig; // gpios used by component

//   void used() {}

//   void available() {}

  GpioService(std::string serviceId) : WebSocketService(serviceId) {}

  void processMsg() {
    Serial.println("[GpioService] reveived message");
    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do doc["time"].as<long>();
    // int speed = jsonMsg["speed"];
    // motor->instantSpeed(speed);

    // iterate over gpio pins from message

    // Print values.
    // Serial.println(service);
    // Serial.println(time);
  }
};