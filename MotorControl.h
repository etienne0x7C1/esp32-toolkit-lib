#include "WebSocketService.h"

class MotorControl : WebSocketService {

    MotorControl(std::string serviceId) : WebSocketService(serviceId){}

    void processMsg()
    {
        Serial.println("[MotorControl] [SID: ] process message");
        // Most of the time, you can rely on the implicit casts.
        // In other case, you can do doc["time"].as<long>();
        int speed = jsonMsg["speed"];
        motor->instantSpeed(speed);

        // Print values.
        // Serial.println(service);
        Serial.println(time);
    }
}