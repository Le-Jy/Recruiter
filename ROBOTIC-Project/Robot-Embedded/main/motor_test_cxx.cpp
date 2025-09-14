#include "motor_test_cxx.hpp"

#include "esp_log.h"
#include "bdc_motor_cxx.hpp"
#include "esp_exception.hpp"
#include "gpio_cxx.hpp"
#include <thread>

#define TAG "BdcMotorTest"


void testMotor(const int gpioLeftMotor1, const int gpioLeftMotor2, const int gpioRightMotor1, const int gpioRightMotor2) {
    try {
        constexpr int pwmFreqHz = 50;
        constexpr int timerResolutionHz = 500000;
        constexpr int groupIdDefault = 0;

        // Create two BDC motors using the provided GPIO pins
        idf::BdcMotor motor1(idf::GPIONum(gpioLeftMotor1), idf::GPIONum(gpioLeftMotor2), pwmFreqHz, groupIdDefault, timerResolutionHz);
        idf::BdcMotor motor2(idf::GPIONum(gpioRightMotor1), idf::GPIONum(gpioRightMotor2), pwmFreqHz, groupIdDefault, timerResolutionHz);

        motor1.enable();
        motor1.setPower(timerResolutionHz/pwmFreqHz * 0.5);
        motor2.enable();
        motor2.setPower(timerResolutionHz/pwmFreqHz * 0.5);

        ESP_LOGI(TAG, "Forward");
        motor1.forward();
        motor2.forward();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        ESP_LOGI(TAG, "Break");
        motor1.brake();
        motor2.brake();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        motor1.setPower(timerResolutionHz/pwmFreqHz * 0.25);
        motor2.setPower(timerResolutionHz/pwmFreqHz * 0.25);

        ESP_LOGI(TAG, "Turn Right");
        motor1.forward();
        motor2.reverse();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        ESP_LOGI(TAG, "Break");
        motor1.brake();
        motor2.brake();

    } catch (idf::ESPException & e) {
        ESP_LOGE(TAG, "GPIO exception occurred: %s", esp_err_to_name(e.error));
        ESP_LOGE(TAG, "stopping.");
    }
}

