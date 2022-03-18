#include <Arduino.h>
#include <FirmwareModule.h>
// #include <FirmwareBase.h>

// class FirmwareModule
// {
int FirmwareModule::cycleCounter = 0;
std::vector<FirmwareModule *> *FirmwareModule::instances = new std::vector<FirmwareModule *>();

// int internalCycleCount = 0;
// int resetCycleCount = pow(2, 10); // the numbers of cycles after which internal counter is increased and cycleCounter is reset

FirmwareModule::FirmwareModule(std::string name ) : moduleName(name)
{
    // FirmwareModule::cycleCounter = 0;
    FirmwareModule::instances->push_back(this);
}

void FirmwareModule::onCycle()
{
    internalCycleCount++; // increase internal counter
}

void FirmwareModule::setup()
{
}

void FirmwareModule::loop()
{
    if (cycleCounter++ >= resetCycleCount)
    {
        cycleCounter = 0; // reset counter
        onCycle();
    }
}

void FirmwareModule::setupAll()
{
    for (auto elem : *FirmwareModule::instances)
    {
        Serial.print("*** ");
        Serial.print(elem->moduleName.c_str());
        Serial.println(" Module ***");
        elem->setup();
    }
    Serial.println("Done setting up all modules!");
}

void FirmwareModule::loopAll()
{
    for (auto elem : *FirmwareModule::instances)
    {
        elem->loop();
    }
}
// };
