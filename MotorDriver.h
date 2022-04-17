#include <Arduino.h>


/**
 * High level motor driver abstract class
 */
class MotorDriver
{
public:
    // when changed impact all instances of MotorDrv class
    static int ACC_DEFAULT_VELOCITY;
    static int BRAKE_DEFAULT_VELOCITY;

    // internal speed tracker
    int speed = 0;

    // common implem
    virtual void instantSpeed(int speedTarget);
    virtual void targetSpeed(int speedTarget, int vel = 20);
    virtual void brake(int vel = 40);
    virtual void test(int max_test_speed);

    // specific motor driver implementation
    virtual void driveMotor(int dutyCycle, bool direction) = 0;
    virtual void enable(bool isEnabled) = 0;
};

