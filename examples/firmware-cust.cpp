/**
 * Firmware modules confguration file: declare all firmware modules 
 * that will be automatically added to the whole firmware
 * 
 * required build env: arduino-esp32
**/

#include <network-module.h>
// #include <filesys-module.h>
#include <web-module.h>
#include <logging-module.h>
#include <module-template.h>

// NetworkModule networkModule();
// FilesysModule filesysModule();
// WebModule webModule();
// TestModule testModule();

NetworkModule *networkModule = new NetworkModule();
// FilesysModule *filesysModule = new FilesysModule();
WebModule *webModule = new WebModule();
LoggingModule *loggingMod = new LoggingModule();
TemplateModule *testModule = new TemplateModule();