#include <adc_cxx.hpp>
#include <esp_exception.hpp>
#include <esp_log.h>
#include <thread>
#include <chrono>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <gpio_cxx.hpp>

#include "line_follower_sensor_cxx.hpp"

// Tag used for ESP_LOGI logging (for identifying log output)
const static char * TAG = "LineFollowerSensor";

using namespace idf;    // Use the idf namespace for ESP-IDF C++ wrappers
using namespace std;    // Use the standard namespace for STL features

void line_follower_sensor(adc_unit_t adc_unit, adc_channel_t adc_channel, idf::AdcOneshot& adc, std::mutex& adcMutex)
{
    /* The functions of GPIO_Output throw exceptions in case of parameter errors or if there are underlying driver errors. */
    try
    {
        constexpr std::chrono::milliseconds time_to_get_mesure{100};

        // Configure the chosen ADC channel with the specified attenuation and bitwidth.
        // Throws ESPException if configuration fails.
        // The mutex and the critical section are in a scope
        {
            std::lock_guard<std::mutex> lock(adcMutex); // Lock the mutex to ensure thread safety
            adc.configure(adc_channel);
        }

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

            // Constants for the mV value to the brut value conversion
            constexpr int brut_val_max_line_track_sensor = 255;
            constexpr int mV_val_max_line_track_sensor = 1650;

            // The measured voltage is after the voltage divider. (we suppose)
            // We get the brut value by dividing the mV value by the maximum mV value and multiplying by the maximum brut value. (classic cross product)
            int lineTrackValueValue = brut_val_max_line_track_sensor * mV_result / mV_val_max_line_track_sensor;

            ESP_LOGI(TAG, "Value of the line tracker sensor: %d", lineTrackValueValue);

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
