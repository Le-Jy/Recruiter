#include "adc_cxx.hpp"
#include <esp_exception.hpp>
#include <esp_log.h>
#include <gpio_cxx.hpp>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <ledc_cxx.hpp>

namespace idf {

AdcOneshot::AdcOneshot(adc_unit_t unit)
{
    _unit = unit;
    _adc_handle = nullptr; // Initialize ADC handle
    channel_configs = {};  // Initialize per-channel configurations
    cali_handles = {};     // Initialize calibration handles map

    // Set up ADC initialization configuration structure.
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = unit,                // Specify which ADC unit to use (ADC_UNIT_1 or ADC_UNIT_2)
        .clk_src = ADC_RTC_CLK_SRC_RC_FAST, // Use fast RC oscillator as clock source (default)
        .ulp_mode = ADC_ULP_MODE_DISABLE, // Disable ULP (Ultra-Low Power) mode for normal ADC operation
    };

    // Create a new ADC oneshot unit instance and store its handle in _adc_handle.
    // If initialization fails, CHECK_THROW will throw an exception.
    CHECK_THROW(adc_oneshot_new_unit(&init_config, &_adc_handle));
}

AdcOneshot::~AdcOneshot() {

    for(auto& pair : cali_handles) {
        adc_cali_delete_scheme_line_fitting(pair.second);
    }
    
    // Clean up and release the ADC unit resource when this object is destroyed.
    // Ensures no resource leaks.
    esp_err_t del_unit_ret_value = adc_oneshot_del_unit(_adc_handle);

    // Check if the deletion was successful. (ESP_ERR_INVALID_ARG or ESP_ERR_NOT_FOUND)
    if (del_unit_ret_value != ESP_OK)
    {
        ESP_LOGE("ADC", "Failed to delete ADC unit: %s", esp_err_to_name(del_unit_ret_value));
    }
}

void AdcOneshot::configure(adc_channel_t channel, adc_atten_t atten, adc_bitwidth_t bitwidth)
{
    // Store channel configuration per channel
    channel_configs[channel] = adc_oneshot_chan_cfg_t{atten, bitwidth};
    
    // Create calibration if necessary
    std::pair<adc_atten_t, adc_bitwidth_t> key = std::make_pair(atten, bitwidth);
    if(cali_handles.find(key) == cali_handles.end()) {
        adc_cali_handle_t handle = NULL;
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = _unit,
            .atten = atten,
            .bitwidth = bitwidth
        };
        CHECK_THROW(adc_cali_create_scheme_line_fitting(&cali_config, &handle));
        cali_handles.emplace(key, handle);
    }

    // Hardware configuration
    CHECK_THROW(adc_oneshot_config_channel(_adc_handle, channel, &channel_configs[channel]));
}

std::pair<adc_unit_t, adc_channel_t> AdcOneshot::ioToChannel(int ioNum) {
    adc_unit_t tmp_adc_unit;
    adc_channel_t tmp_adc_channel;

    // Convert a GPIO number to the corresponding ADC unit and channel.
    CHECK_THROW(adc_oneshot_io_to_channel(ioNum, &tmp_adc_unit, &tmp_adc_channel));

    return std::make_pair(tmp_adc_unit, tmp_adc_channel);
}

int AdcOneshot::readRaw(adc_channel_t channel) {
    int raw_result; // Variable to hold the raw ADC result (integer)
    // Read the raw ADC value from the specified channel using the previously configured settings.
    // Throws exception on error.
    CHECK_THROW(adc_oneshot_read(_adc_handle, channel, &raw_result));
    // Return the raw ADC reading (range depends on bitwidth, e.g., 0-4095 for 12 bits)
    return raw_result;
}

int AdcOneshot::readMlVolt(adc_channel_t channel)
{
    int raw = readRaw(channel);
    
    // Retrieve channel configuration
    auto config_it = channel_configs.find(channel);
    if(config_it == channel_configs.end()) {
        throw ESPException(ESP_ERR_INVALID_ARG);
    }
    
    // Find calibration handle
    auto cali_key = std::make_pair(config_it->second.atten, config_it->second.bitwidth);
    auto cali_it = cali_handles.find(cali_key);
    if(cali_it == cali_handles.end()) {
        throw ESPException(ESP_ERR_INVALID_STATE);
    }

    // Conversion
    int voltage = 0;
    CHECK_THROW(adc_cali_raw_to_voltage(cali_it->second, raw, &voltage));
    return voltage;
}

} // namespace idf