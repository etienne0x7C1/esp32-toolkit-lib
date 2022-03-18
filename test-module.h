// #include <FirmwareBase.h>

/**
 * simple example of module implementation 
 * loging each time an internal cycle occurs
 */

class TestModule : public FirmwareModule
{
    void onCycle()
    {
        internalCycleCount++;
        Serial.print("cycle #");
        Serial.println(internalCycleCount);
    }
};
