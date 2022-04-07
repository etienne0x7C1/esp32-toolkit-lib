#include <FirmwareModule.h>
#include <WebSocketService.h>

class CamControls : FirmwareModule
{
public:
    CamControls() : FirmwareModule("CamControls"){};

    void process()
    {
        Serial.println("[CamControls] process message");
        // Most of the time, you can rely on the implicit casts.
        // In other case, you can do doc["time"].as<long>();
        // const char *service = jsonMsg["service"];
        int count = jsonMsg["counter"];

//           const char *sensor = jsonMsg["sensor"];
//   long time = jsonMsg["time"];
//   double latitude = jsonMsg["data"][0];
//   double longitude = jsonMsg["data"][1];

//   // Print values.
//   Serial.println(sensor);
//   Serial.println(time);
//   Serial.println(latitude, 6);
//   Serial.println(longitude, 6);

        // Print values.
        Serial.println(count);
    }
};

