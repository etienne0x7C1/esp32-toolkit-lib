#include <FirmwareModule.h>
#include <LittleFS.h>
#include <fs-utils.h>

class FilesysModule : public FirmwareModule
{
public:
    FilesysModule() : FirmwareModule("Filesystem")
    {
    }

    void setup()
    {
        FirmwareModule::setup();

        if (!LittleFS.begin(true))
        {
            Serial.println("[LittleFS] error while mounting filesystem");
        }
        Serial.println("[LittleFS] mounted successfully!");

        File file = LittleFS.open("/test.txt", "r");
        if (!file)
        {
            Serial.println("[LittleFS] Failed to open file for reading");
            return;
        }

        Serial.println("[LittleFS] File Content:");
        while (file.available())
        {
            Serial.write(file.read());
        }
        file.close();

        listDir(LittleFS, "/", 0);

        Serial.println("[LittleFS] Done");
    }
};