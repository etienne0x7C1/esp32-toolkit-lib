#include <FirmwareModule.h>
#include <LittleFS.h>
#include <fs-utils.h>

class FilesysModule : public FirmwareModule
{
    void setup()
    {
        Serial.println("** Filesystem **");

        if (!LittleFS.begin(true))
        {
            Serial.println("error while mounting filesystem");
        }
        Serial.println("mounted successfully!");

        File file = LittleFS.open("/test.txt", "r");
        if (!file)
        {
            Serial.println("Failed to open file for reading");
            return;
        }

        Serial.println("File Content:");
        while (file.available())
        {
            Serial.write(file.read());
        }
        file.close();

        listDir(LittleFS, "/", 0);

        Serial.println("OK");
        Serial.println("");
    }
};