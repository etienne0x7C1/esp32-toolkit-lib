/**
 * main entry point 
 * includes firmware modules config file and start firmware execution
**/

#include <iostream>
#include <Arduino.h>
#include <FirmwareModule.h>

/**
 * uncomment chosen firmware configuration below
 * use appropriate build environment in platformio (specified in chosen source file)
 */

// #include "examples/firmware-mini.cpp"
#include "examples/firmware-base.cpp"
// #include "examples/firmware-full.cpp"
// #include "examples/firmware-cust.cpp"

/**
 * setup
 */
void setup()
{
  Serial.begin(115200);
  Serial.println("[ESP32] First log!");

  // Init all modules
  FirmwareModule::setupAll();
}

/**
 * main loop
 */
void loop()
{
  // Refresh all modules
  FirmwareModule::loopAll();
}