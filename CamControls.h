#include <FirmwareModule.h>
#include <WebSocketService.h>

class CamControls : FirmwareModule, WebSocketService
{
public:
    CamControls() : FirmwareModule("CamControls"), WebSocketService("camcontrols"){};

    void process()
    {
        Serial.println("[CamControls] process message");
        // Most of the time, you can rely on the implicit casts.
        // In other case, you can do doc["time"].as<long>();
        // const char *service = jsonMsg["service"];
        int count = jsonMsg["counter"];

        // Print values.
        Serial.println(count);
    }
};