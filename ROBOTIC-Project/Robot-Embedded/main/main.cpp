#include "adc_cxx.hpp"

#include <functional>
#include <thread>
#include <gpio_cxx.hpp>

#include "wifi.hpp"
#include "battery_manager_cxx.hpp"
#include "motor_test_cxx.hpp"
#include "line_follower_sensor_cxx.hpp"

using namespace idf;    // Use ESP-IDF C++ wrapper namespace
using namespace std;    // Use standard C++ library namespace

#include <driver/gpio.h>

// app_main is the entry point for ESP-IDF applications when using C++.
// The extern "C" ensures the function name is not mangled, so ESP-IDF can find and call it.
extern "C" void app_main(void)
{
     //Unique call to install ISR service
    gpio_install_isr_service(0);

    int BATTERY_GPIO = 36;
    int LINE_TRACK_GPIO = 39;

    // Convert GPIO 36 to its corresponding ADC unit and channel. The battery gpio.
    // Returns a std::pair<adc_unit_t, adc_channel_t>.
    std::pair<adc_unit_t, adc_channel_t> channelBattery = AdcOneshot::ioToChannel(BATTERY_GPIO);

    // Convert GPIO 39 to its corresponding ADC unit and channel. The line track sensor gpio.
    // Returns a std::pair<adc_unit_t, adc_channel_t>.
    std::pair<adc_unit_t, adc_channel_t> channelLineSensor = AdcOneshot::ioToChannel(LINE_TRACK_GPIO);

    assert(channelBattery.first == channelLineSensor.first); // Check if both channels are on the same ADC unit

    // Define ADC configuration constants:
    adc_unit_t adc_unit = channelBattery.first;

    adc_channel_t adc_channel_battery = channelBattery.second;
    adc_channel_t adc_channel_line_sensor = channelLineSensor.second;

    // Create an ADC oneshot object for the specified ADC unit.
    // Throws ESPException on initialization error.
    AdcOneshot adc(adc_unit);

    // Create the mutex for the ADC object.
    // This mutex is used to synchronize access to the ADC object across multiple threads.
    std::mutex adcMutex;

    // Create a new std::thread that runs the batteryManager function.
    // This allows battery monitoring and buzzer control to run independently of the main thread.
    // The thread will execute the batteryManager function defined elsewhere.
    // DO NOT DELETE THIS PART: Required for battery safety logic.
    thread batteryManagerThread(batteryManager, adc_unit, adc_channel_battery, std::ref(adc), std::ref(adcMutex));

    // Create a new std::thread that runs the line_follower_sensor function.
    // This allows line following sensor monitoring to run independently of the main thread.
    thread lineFollowerSensorThread(line_follower_sensor, adc_unit, adc_channel_line_sensor, std::ref(adc), std::ref(adcMutex));

    // ---------------------------------------------------------------------
    // Place any additional application initialization or tasks here.
    // For example, you could start other threads, initialize peripherals,
    // or run your main application logic in this section.
    // ---------------------------------------------------------------------
    
    constexpr int RIGHT_MOTOR_GPIO_1 = 4;
    constexpr int RIGHT_MOTOR_GPIO_2 = 2;
    constexpr int LEFT_MOTOR_GPIO_1 = 12;
    constexpr int LEFT_MOTOR_GPIO_2 = 13;
    activate_wifi_and_start_json_server(LEFT_MOTOR_GPIO_1, LEFT_MOTOR_GPIO_2, RIGHT_MOTOR_GPIO_1, RIGHT_MOTOR_GPIO_2);


    /*testMotor(LEFT_MOTOR_GPIO_1, LEFT_MOTOR_GPIO_2, RIGHT_MOTOR_GPIO_1, RIGHT_MOTOR_GPIO_2);*/

    // Wait for the battery manager thread and the line follower sensor thread to finish before exiting app_main.
    // join() blocks until the thread completes.
    // In most embedded applications, this means app_main will not exit
    // unless batteryManager or line_follower_sensor returns or throws an exception.
    batteryManagerThread.join();
    lineFollowerSensorThread.join();
}

