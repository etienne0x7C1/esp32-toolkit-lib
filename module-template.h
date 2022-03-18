#include <FirmwareModule.h>

/**
 * This is simple template showing an example of module implementation
 * doing nothing but loging each time an internal cycle happens
 */

class TemplateModule : public FirmwareModule
{
public:
    /**
     * called once
     */
    void setup()
    {
        FirmwareModule::setup();
    }

    /**
     * main loop
     */
    void loop()
    {
        FirmwareModule::loop();
    }

    /**
     * substitute to main loop
     * called each time an internal cycle is done
     */
    void onCycle()
    {
        internalCycleCount++;
        Serial.print("cycle #");
        Serial.println(internalCycleCount);
    }
};
