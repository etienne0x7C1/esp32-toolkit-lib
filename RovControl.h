#include <FirmwareModule.h>
#include <WebSocketService.h>

class RovControl : FirmwareModule, WebSocketService
{
public:
    RovControl() : FirmwareModule("RovControl"), WebSocketService("rovcontrol"){};

    void process()
    {
        Serial.println("[RoverControl] process message");
        // Most of the time, you can rely on the implicit casts.
        // In other case, you can do doc["time"].as<long>();
        int time = jsonMsg["counter"];

        // Print values.
        // Serial.println(service);
        Serial.println(time);
    }
};