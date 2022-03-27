#pragma once

#include <cmath>
#include <vector>
// #include <iostream>
#include <string>

/**
 * Firmware add-on, plugin, tool to implement feature
 * called by the main firmware
 * */

class FirmwareModule
{
public:
    static int cycleCounter;
    static std::vector<FirmwareModule *> *instances;

    int internalCycleCount = 0;
    int resetCycleCount = pow(2, 20); // the numbers of cycles after which internal counter is increased and cycleCounter is reset
    std::string moduleName;

public:
    FirmwareModule(std::string moduleName = "defaultmodule");

    virtual void onCycle();

    virtual void setup();

    virtual void loop();

    /**
    * Static 
    */
    static void setupAll();
    static void loopAll();
};