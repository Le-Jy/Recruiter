#include "motor_controller.hpp"
#include <esp_log.h>

// Tag used for ESP_LOGI logging (for identifying log output)
const static char* TAG =  "MotorController";

MotorController::MotorController(const int gpioLeftMotor1, const int gpioLeftMotor2, const int gpioRightMotor1, const int gpioRightMotor2)
    : _motorLeft(idf::GPIONum(gpioLeftMotor1), idf::GPIONum(gpioLeftMotor2), PWM_FREQ_HZ, GROUP_ID_DEFAULT, TIMER_RESOLUTION_HZ),
      _motorRight(idf::GPIONum(gpioRightMotor1), idf::GPIONum(gpioRightMotor2), PWM_FREQ_HZ, GROUP_ID_DEFAULT, TIMER_RESOLUTION_HZ)
      {
        _motorLeft.enable();
        _motorRight.enable();
      }

// Set motor power (push command to queue)
void MotorController::setMotorsPower(float left, float right) {
    // Simulate motor control (replace with real motor control code)
    moveMotor(left, _motorLeft);
    moveMotor(right, _motorRight);
    ESP_LOGI(TAG, "Controlling motor: Left = %f, Right = %f \n", left, right);
}

void MotorController::moveMotor(float powerValue, idf::BdcMotor& motor) {
    if (powerValue > 0) {
        motor.setPower(TIMER_RESOLUTION_HZ/PWM_FREQ_HZ * powerValue);
        motor.forward();
    } else if (powerValue < 0) {
        motor.setPower(-(TIMER_RESOLUTION_HZ/PWM_FREQ_HZ * powerValue));
        motor.reverse();
    } else {
        motor.setPower(0);
        motor.brake();
    }
}