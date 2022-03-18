/**
 * Firmware modules confguration file: declare all firmware modules 
 * that will be automatically added to the whole firmware
 * 
 * base version including most common functions: network, web services, ota
 * 
 * required build env: arduino-esp32
**/

#include <network-module.h>
#include <filesys-module.h>
#include <web-module.h>
#include <module-template.h>

// NetworkModule networkModule();
// FilesysModule filesysModule();
// WebModule webModule();
// TestModule testModule();

NetworkModule *networkModule = new NetworkModule();
FilesysModule *filesysModule = new FilesysModule();
WebModule *webModule = new WebModule();
TemplateModule *testModule = new TemplateModule();