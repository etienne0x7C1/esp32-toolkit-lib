/**
 * Low level drivers for specific model implementations
 */

/**
 *  BTS7960 model
 */
class MotorDriver_BTS7960 : public MotorDriver, GpioService {

    pin

  // PWM properties
  const int pwmFreq = 10000;
  const int pwmRes = 8;

public:
  int lPin, rPin;
  int lPwmChannel, rPwmChannel;

  MotorDriver_BTS7960(int rPin, int lPin, int lPwmChannel, int rPwmChannel)
      : lPin(lPin), rPin(rPin), lPwmChannel(lPwmChannel),
        rPwmChannel(rPwmChannel) {
    // configure LED PWM functionalitites
    ledcSetup(rPwmChannel, pwmFreq, pwmRes);
    ledcSetup(lPwmChannel, pwmFreq, pwmRes);

    // attach channel to controling GPIO
    ledcAttachPin(rPin, rPwmChannel);
    ledcAttachPin(lPin, lPwmChannel);
  }

  void forward(int dutyCycle) {
    ledcWrite(lPwmChannel, 0);
    ledcWrite(rPwmChannel, dutyCycle);
  }

  void backward(int dutyCycle) {
    ledcWrite(lPwmChannel, dutyCycle);
    ledcWrite(rPwmChannel, 0);
  }

  //   void driveMotor(int dutyCycle, bool direction) override {
  //     // move forward
  //     if (direction) {
  //       ledcWrite(lPwmChannel, 0);
  //       ledcWrite(rPwmChannel, dutyCycle);
  //     }
  //     // move backward
  //     else {
  //       ledcWrite(lPwmChannel, dutyCycle);
  //       ledcWrite(rPwmChannel, 0);
  //     }
  //   }

  void enable(bool isEnabled) override {}
};