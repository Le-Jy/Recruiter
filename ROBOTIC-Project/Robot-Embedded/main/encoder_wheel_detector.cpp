#include "encoder_wheel_detector.hpp"
#include "esp_log.h"

EncoderWheelDetector::EncoderWheelDetector(gpio_num_t gpio, QueueHandle_t queue, int side)
    : gpio(gpio), queue(queue), side(side) {
    // Basic initialization; actual GPIO setup is done in start()
}

EncoderWheelDetector::~EncoderWheelDetector() {
    stop(); // Ensures the interrupt is detached when the object is destroyed
}

void IRAM_ATTR EncoderWheelDetector::handle_interrupt(void *args) {
    EncoderWheelDetector* self = static_cast<EncoderWheelDetector*>(args);

    // --- ISR context: ---
    // - Do not call blocking functions (no printf, malloc, etc.)
    // - Shared variables must be volatile
    // - Only do atomic/simple operations

    // Increment counters before creating the event to guarantee order
    const size_t new_value = self->value++;

    EncoderEvent event = {
        .index = self->side,
        .value = new_value
    };

    // Non-blocking send to the queue (ISR-safe version)
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t status = xQueueSendFromISR(
        self->queue, 
        &event, 
        &xHigherPriorityTaskWoken
    );

    // Minimal error handling
    if(status != pdPASS) {
        // Queue is full - event lost!
        ESP_LOGI("ENCODER_WHEEL", "Event lost");
    }
}

void EncoderWheelDetector::start() {
    gpio_config_t cfg = {
        .pin_bit_mask = (1ULL << gpio),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE
    };

    // Apply GPIO configuration
    esp_err_t ret = gpio_config(&cfg);
    if(ret != ESP_OK) {
        // If configuration fails (already used, etc.)
        ESP_LOGE("ENCODER", "GPIO config error %d: %s", gpio, esp_err_to_name(ret));
        return;
    }

    // Attach the ISR to the GPIO
    ret = gpio_isr_handler_add(gpio, handle_interrupt, this);
    if(ret != ESP_OK) {
        ESP_LOGE("ENCODER", "ISR handler add error %d: %s", gpio, esp_err_to_name(ret));
    }
}

void EncoderWheelDetector::stop() {
    // Detach the ISR but do not uninstall the global ISR service
    esp_err_t ret = gpio_isr_handler_remove(gpio);
    if(ret != ESP_OK) {
        ESP_LOGE("ENCODER", "ISR handler remove error %d: %s", gpio, esp_err_to_name(ret));
    }

    // Reset the GPIO to default state
    gpio_reset_pin(gpio);
}
