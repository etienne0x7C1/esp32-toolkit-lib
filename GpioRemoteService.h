#include "WebSocketService.h"
#include <map>
enum GPIO_ACTIONS { READ, WRITE, INIT };

enum GPIO_TYPES { ANALOG_PIN, PWM_PIN };

struct GPIO_STATE {
  int val;
  int freq;
  int res;
  int pwmChannel;
  GPIO_TYPES type;
};

/**
 * Perform GPIO operation remotely
 */
class GpioRemoteService : WebSocketService {
  static std::map<int, GPIO_STATE> *gpioStateMap;

public:
  //   static std::vector<GpioService *> *instances;              // the
  //   registered components to gpio service std::vector<int> *pinConfig; //
  //   gpios used by component

  //   void used() {}

  //   void available() {}

  GpioRemoteService(std::string serviceId) : WebSocketService(serviceId) {}

  void processMsg() {
    Serial.println("[GpioService] reveived message");
    // extract the values
    JsonArray array = jsonMsg["gpios"];
    for (JsonVariant gpio : array) {
      GPIO_ACTIONS action = gpio["action"];
      int pin = gpio["pin"];
      // int val = gpio["val"];
      // GPIO_TYPES type = gpio["type"];

      Serial.print("Pin: ");
      Serial.print(pin);

      // write/read mode?
      bool isWriteMode = true; // todo
      // pwm?
      bool isPWM = true; // todo
      // initialized?
      // if (!gpioStateMap.contains(pin)) {
      if (gpioStateMap->find(pin) == gpioStateMap->end()) {
        // init gpio
        Serial.println("Init as PWM ");

        if (isPWM) {
          GPIO_STATE pinState;
          pinState.val = 0, pinState.freq = 10000, pinState.res = 8;
          pinState.pwmChannel = gpio["pwmChan"];
          gpioStateMap->insert({pin, pinState});
          Serial.print("gpioStateMap size is now: ");
          Serial.println(gpioStateMap->size());
          Serial.print("configuring pin ");
          pinMode(pin, OUTPUT);
          ledcSetup(pinState.pwmChannel, pinState.freq, pinState.res);
          ledcAttachPin(pin, pinState.pwmChannel);
        }
      }
      if (isPWM && isWriteMode) {
        Serial.print(" => write value: ");
        int dutyCycle = gpio["val"];
        Serial.println(dutyCycle);
        GPIO_STATE gpioState = gpioStateMap->at(pin);
        Serial.print(dutyCycle);
        ledcWrite(gpioState.pwmChannel, dutyCycle);
      }
    }
    Serial.println("");
    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do doc["time"].as<long>();
    // int speed = jsonMsg["speed"];
    // motor->instantSpeed(speed);

    // iterate over gpio pins from message

    // Print values.
    // Serial.println(service);
    // Serial.println(time);
  }
};

std::map<int, GPIO_STATE> *GpioRemoteService::gpioStateMap =
    new std::map<int, GPIO_STATE>();