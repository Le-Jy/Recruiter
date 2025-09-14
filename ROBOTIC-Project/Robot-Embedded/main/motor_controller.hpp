#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

#include <thread>
#include <utility>
#include <iostream>
#include "bdc_motor_cxx.hpp" // Include the header for idf::BdcMotor

class MotorController {
public:
    MotorController(const int gpioLeftMotor1, const int gpioLeftMotor2, const int gpioRightMotor1, const int gpioRightMotor2);

    void setMotorsPower(float left, float right);

private:
    void motorControlLoop();
    void moveMotor(float powerValue, idf::BdcMotor& motor); // Pass motor by reference

    // Motor objects
    idf::BdcMotor _motorLeft;
    idf::BdcMotor _motorRight;

    // Constants
    static const uint32_t PWM_FREQ_HZ = 50;
    static const uint32_t TIMER_RESOLUTION_HZ = 500000;
    static const int GROUP_ID_DEFAULT = 0;
};

#endif
