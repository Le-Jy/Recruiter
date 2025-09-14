#include "wifi.hpp"
#include "esp_exception.hpp"
#include "wifi_cxx.hpp"
#include "esp_event_cxx.hpp"
#include "jsonrpctcpserver.hpp"
#include "nvs_flash.h"
#include <thread>
#include <iostream>
#include <ArduinoJson.hpp>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "motor_controller.hpp"
#include "encoder_wheel_detector.hpp"

#define TAG "Wifi"
constexpr int LEFT_SIDE = 1;
constexpr int RIGHT_SIDE = 0;
constexpr int QUEUE_SIZE = 4;

using namespace std::chrono_literals;

QueueHandle_t motorCommandQueue;

void motorControlThread(const int gpioLeftMotor1, const int gpioLeftMotor2, const int gpioRightMotor1, const int gpioRightMotor2) {
    MotorController motorController(gpioLeftMotor1, gpioLeftMotor2, gpioRightMotor1, gpioRightMotor2);

    std::pair<float, float> command;
    while (true) {
        if (xQueueReceive(motorCommandQueue, &command, portMAX_DELAY) == pdTRUE) {
            motorController.setMotorsPower(command.first, command.second);
        }
    }
}

void encoderWheelThread(JsonRpcTcpServer& jsonRpcTcpServer) {
    QueueHandle_t encoderQueue = xQueueCreate(QUEUE_SIZE, sizeof(struct EncoderEvent));
    EncoderWheelDetector encoderWheelDetectorLeft(GPIO_NUM_26, encoderQueue, LEFT_SIDE);
    EncoderWheelDetector encoderWheelDetectorRight(GPIO_NUM_18, encoderQueue, RIGHT_SIDE);

    struct EncoderEvent event;
    encoderWheelDetectorLeft.start();
    encoderWheelDetectorRight.start();
    std::array<size_t, 2> changed_counts_encoder = {0, 0};


    while(true) {
        if (xQueueReceive(encoderQueue, &event, portMAX_DELAY) == pdTRUE) {
            ArduinoJson::StaticJsonDocument<128> doc;
            ArduinoJson::JsonObject params =  doc.to<ArduinoJson::JsonObject>();
            changed_counts_encoder[event.index]++;
            params["index"] = event.index;
            params["value"] = event.value;
            params["changedCount"] = changed_counts_encoder[event.index];
            jsonRpcTcpServer.sendNotification("encoderWheelValue",params);
            std::cout << "index=" << event.index << ", value=" << event.value << ", changedCount=" << changed_counts_encoder[event.index] << std::endl;
        }
    }
}

void activate_wifi_and_start_json_server(const int gpioLeftMotor1, const int gpioLeftMotor2, const int gpioRightMotor1, const int gpioRightMotor2) {
    try {
        // Initialize NVS
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);

        // Init event loop
        idf::event::ESPEventLoop eventLoop;

        // Initialize Wifi
        idf::Wifi wifi(eventLoop);
        ESP_LOGI(TAG, "Starting STA");
        wifi.setMode(WIFI_MODE_STA);

        // Set the config for the wifi
         wifi.setConfigSta(CONFIG_ESP_WIFI_SSID, CONFIG_ESP_WIFI_PASSWORD, WIFI_AUTH_WPA_WPA2_PSK);

        // Start the wifi
        wifi.start();

        // Wait for the wifi to be started and display connection information
        ESP_LOGI(TAG, "Waiting for connection");
        wifi.waitConnected();
        ESP_LOGI(TAG, "Connected");
        auto ipInfo = wifi.waitIp();
        std::cout << "My IP : " << ipInfo.ip << std::endl;

        // Create an instance of Json RCP server on TCP port 6543
        constexpr int jsonRpcTcpServerPort = 6543;
        JsonRpcTcpServer jsonRpcTcpServer(jsonRpcTcpServerPort);
        ESP_LOGI(TAG, "JsonRpcTcpServer created");

        // When a new client connect send it a jsonRCP notification
        jsonRpcTcpServer.bindOnConnectSendNotification("setIsReady",
              [](){return ArduinoJson::DynamicJsonDocument(10);});

        // Bind notification handler for setMotorsPower
        jsonRpcTcpServer.bindNotification("setMotorsPower", [](ArduinoJson::DynamicJsonDocument params) {
            float leftValue = params["leftValue"].as<float>();
            float rightValue = params["rightValue"].as<float>();

            std::pair<float, float> command(leftValue, rightValue);
            xQueueSendToBack(motorCommandQueue, &command, 0); // Non-blocking send
        });

        motorCommandQueue = xQueueCreate(QUEUE_SIZE, sizeof(std::pair<float, float>));
        std::thread motorThread(motorControlThread, gpioLeftMotor1, gpioLeftMotor2, gpioRightMotor1, gpioRightMotor2);
        motorThread.detach();

         // Create and start encoder wheel threads
        // Could replace threads by xTask from RTOS libs TODO
        std::thread encoderThreadLeft(encoderWheelThread, std::ref(jsonRpcTcpServer));
        encoderThreadLeft.detach();

        std::thread encoderThreadRight(encoderWheelThread, std::ref(jsonRpcTcpServer));
        encoderThreadRight.detach();

        // Wait and serve new client
        jsonRpcTcpServer.listen();
    } catch (idf::ESPException & e) {
        std::cout << "Exception occurred: " << esp_err_to_name(e.error) << std::endl
                 << "stopping." << std::endl;
    }
}
