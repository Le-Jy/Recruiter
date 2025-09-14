#include <cstdlib>
#include <chrono>
#include <thread>

#include "adc_cxx.hpp"
#include "battery_manager_cxx.hpp"
#include <esp_exception.hpp>
#include <esp_log.h>
#include <gpio_cxx.hpp>
#include <ledc_cxx.hpp>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Tag used for ESP_LOGI logging (for identifying log output)
const static char * TAG = "Buzzer";

using namespace idf;    // Use the idf namespace for ESP-IDF C++ wrappers
using namespace std;    // Use the standard namespace for STL features

void batteryManager(adc_unit_t adc_unit, adc_channel_t adc_channel, idf::AdcOneshot& adc, std::mutex& adcMutex)
{
    /* The functions of GPIO_Output throw exceptions in case of parameter errors or if there are underlying driver errors. */
    try
    {
        constexpr std::chrono::seconds time_to_get_mesure{1};
        constexpr std::chrono::milliseconds time_to_buzz{100};

        constexpr int minimal_not_accepted_mV = 0;
        constexpr int maximal_not_accepted_mV = 6000;

        int gpio_12 = 12;
        int gpio_16 = 16;

        constexpr int hz_buzz_value = 200;

        // Configure the chosen ADC channel with the specified attenuation and bitwidth.
        // Throws ESPException if configuration fails.
        // The mutex and the critical section are in a scope
        {
            std::lock_guard<std::mutex> lock(adcMutex); // Lock the mutex to ensure thread safety
            adc.configure(adc_channel);
        }

        // Set up a PWM timer for the buzzer:
        // - Use timer 0, hz_buzz_value Hz frequency, low speed mode, 13-bit resolution.
        idf::LedcTimer buzzerPwmTimer(LEDC_TIMER_0, hz_buzz_value, LEDC_LOW_SPEED_MODE, LEDC_TIMER_13_BIT);

        // Pause the timer initially so the buzzer is off.
        buzzerPwmTimer.pause();

        // Set up a PWM channel:
        // - Use channel 0, link to the above timer, output on GPIO 16, duty cycle of 1<<12.
        idf::LedcChannel ledcChannel0(LEDC_CHANNEL_0, buzzerPwmTimer, idf::GPIONum(gpio_16), 1<<12);

        // Main loop: repeatedly check the ADC value and control the buzzer accordingly.
        while (true)
        {
            // Get next mesure in time_to_get_mesure second
            std::this_thread::sleep_for(time_to_get_mesure);

            // Perform a single ADC measurement and convert the result to millivolts.
            // Throws ESPException on read error.
            // The mutex and the critical section are in a scope
            int mV_result = 0;
            {
                std::lock_guard<std::mutex> lock(adcMutex); // Lock the mutex to ensure thread safety
                mV_result = adc.readMlVolt(adc_channel);
            }

            // Constants for voltage divider resistors (from board schematic)
            constexpr int R1_value = 10000;  // Top resistor in voltage divider (10kΩ)
            constexpr int R2_value = 22000;  // Bottom resistor in voltage divider (22kΩ)

            // The measured voltage is after the voltage divider.
            // To get the actual input voltage (before the divider), use the inverse divider formula:
            //   Vin = Vmeasured * (R1 + R2) / R1
            // This corrects for the voltage drop across the divider.
            int Vin = mV_result * (R2_value + R1_value) / R1_value;

            // If the measured voltage is between 0 and 6000 mV, activate the buzzer.
            if (Vin > minimal_not_accepted_mV && Vin < maximal_not_accepted_mV)
            {
                ESP_LOGI(TAG, "Battery Not Ok: %dmV", Vin);

                buzzerPwmTimer.resume();

                // Wait for 100 millisecond while the buzzer is active.
                std::this_thread::sleep_for(time_to_buzz);

                // Pause the buzzer (stop PWM output) until the next check.
                buzzerPwmTimer.pause();
            }
            else 
            {
                if (Vin == 0)
                {
                    ESP_LOGI(TAG, "Battery disconnected");
                }

                else
                {
                    ESP_LOGI(TAG, "Battery OK: %dmV", Vin);
                }
            }

            vTaskDelay(pdMS_TO_TICKS(100)); // Yield to RTOS scheduler
        }
    }
    catch (GPIOException &e) 
    {
        // Handle exceptions related to GPIO operations (e.g., invalid pin, driver errors).
        printf("GPIO exception occurred: %s\n", esp_err_to_name(e.error));
        printf("stopping.\n");
    }
    catch (ESPException &e)
    {
        // Handle exceptions related to ESP-IDF operations (e.g., ADC errors).
        printf("ADC exception occurred: %s\n", esp_err_to_name(e.error));
        printf("stopping.\n");
    }
    catch (std::exception &e)
    {
        // Handle standard C++ exceptions (e.g., std::runtime_error).
        printf("Standard exception occurred: %s\n", e.what());
        printf("stopping.\n");
    }
    catch (...)
    {
        // Catch any other unknown exceptions.
        printf("Unknown exception occurred.\n");
        printf("stopping.\n");
    }
}
