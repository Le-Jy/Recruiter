#pragma once

/**
 * @file encoder_wheel_dheel_detector.hpp
 * @brief Encoder wheel detection handler with GPIO interrupts
 */

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

/**
 * @struct EncoderEvent
 * @brief Data structure representing encoder wheel events
 */
struct EncoderEvent {
    int index;
    size_t value;
};

/**
 * @class EncoderWheelDetector
 * @brief Handles encoder wheel detection via GPIO interrupts
 * 
 * Features:
 * - GPIO interrupt configuration
 * - FreeRTOS queue integration
 * - Thread-safe counters
 */
class EncoderWheelDetector {
public:
    /**
     * @brief Construct a new Encoder Wheel Detector object
     * @param gpio_num GPIO pin number for encoder input
     * @param queue FreeRTOS queue handle for event transmission
     * @param side Encoder index (0=right, 1=left)
     */
    EncoderWheelDetector(gpio_num_t gpio_num, QueueHandle_t queue, int side);
    
    /**
     * @brief Destroy the Encoder Wheel Detector object
     */
    ~EncoderWheelDetector();

    /**
     * @brief Start encoder detection
     */
    void start();

    /**
     * @brief Stop encoder detection
     */
    void stop();

private:
    /**
     * @brief Static ISR handler wrapper
     * @param args Pointer to EncoderWheelDetector instance
     */
    static void IRAM_ATTR handle_interrupt(void *args);

    gpio_num_t gpio;           ///< GPIO pin number
    QueueHandle_t queue;       ///< FreeRTOS event queue handle
    int side;                  ///< Encoder index identifier
    volatile size_t value = 0;    ///< Auto-incrementing value (ISR-safe)
};
