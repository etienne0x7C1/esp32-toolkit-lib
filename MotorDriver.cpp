#include <MotorDriver.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

/**
 * Instantaneous set motor speed
 * Bridge between high and low level implementation
 */
void MotorDriver::instantSpeed(int speed)
{
    int dutyCycle = speed > 0 ? min(255, speed) : min(255, -speed);
    bool dir = speed > 0 ? 1 : 0;
    driveMotor(dutyCycle, dir);
}

/**
* Reach target speed at specified acceleration
*/
void MotorDriver::targetSpeed(int speedTarget, int vel)
{
    if (speedTarget != speed)
    {
        cout << "MOTOR RECEIVED ORDER " << speedTarget << endl;
        int timeStepMs = 1000 / vel;
        const int speedInc = (speedTarget - speed) > 0 ? 1 : -1;
        while (speed != speedTarget)
        {
            // cout << "speed:" << speed << endl;
            // Serial.println(str.c_str());
            // motorL->speedDrive(speed);
            instantSpeed(speed);
            speed += speedInc;
            this_thread::sleep_for(chrono::milliseconds(timeStepMs));
        }
        cout << "TARGET REACHED " << speed << endl;
    }
}

/**
* Deccelerate/brake at specified velocity until motor is completely stopped
*/
void MotorDriver::brake(int vel)
{
    cout << "BRAKING..." << endl;
    int timeStepMs = 1000 / vel;
    const int speedInc = speed > 0 ? -1 : 1;
    // Brake
    while (speed)
    {
        speed += speedInc;
        instantSpeed(speed);
        this_thread::sleep_for(chrono::milliseconds(timeStepMs));
    }
    cout << "MOTOR STOPPED" << endl;
}

void MotorDriver::test(int max_test_speed)
{
    // MotorDriver::ACC_DEFAULT_VELOCITY = 20;
    // MotorDriver::BRAKE_DEFAULT_VELOCITY = 40;
    cout << "BEGIN TEST!" << endl;

    cout << "TEST: FORWARD" << endl;

    targetSpeed(max_test_speed);
    // sleep(2);
    brake();

    sleep(1);

    cout << "TEST: BACKWARD" << endl;

    targetSpeed(-max_test_speed);
    // sleep(2);
    brake();

    sleep(2);

    cout << "END TEST!" << endl;
}