#pragma once

#ifdef __cpp_exceptions

#include <utility>
#include <map>

#include <hal/adc_types.h>
#include <esp_adc/adc_oneshot.h>
#include <esp_adc/adc_cali_scheme.h>

namespace idf {

class AdcOneshot
{
public:
    /**
     * @brief Create a handle to a specific ADC unit
     *
     * @note This API is thread-safe. For more details, see ADC programming guide
     *
     * @param[in] unit Unit to allocate
     *
     * @throw
     *        - idf::ESPException(ESP_ERR_INVALID_ARG) if invalid arguments
     *        - idf::ESPException(ESP_ERR_NO_MEM) if no memory
     *        - idf::ESPException(ESP_ERR_NOT_FOUND) if the ADC peripheral to be claimed is already in use
     *        - idf::ESPException(ESP_FAIL) if lock source isn't initialised correctly
     */
    AdcOneshot(adc_unit_t unit);

    /**
     * @brief Delete the ADC unit handle
     *
     * @note This API is thread-safe. For more details, see ADC programming guide
     */
    ~AdcOneshot();

    /**
     * @brief Set ADC oneshot mode required configurations
     *
     * @param[in] channel ADC channel to be configured
     * @param[in] atten ADC attenuation (e.g., ADC_ATTEN_DB_0, ADC_ATTEN_DB_2_5, etc.)
     * @param[in] bitwidth ADC conversion result bits (e.g., ADC_WIDTH_BIT_12)
     */
    void configure(adc_channel_t channel, adc_atten_t atten = ADC_ATTEN_DB_12, adc_bitwidth_t bitwidth = ADC_BITWIDTH_DEFAULT);

    /**
     * @brief Get ADC channel from the given GPIO number
     */
    static std::pair<adc_unit_t, adc_channel_t> ioToChannel(int ioNum);

    /**
     * @brief Get one ADC conversion raw result
     */
    int readRaw(adc_channel_t channel);

    /**
     * @brief Get one ADC conversion millivolt result
     */
    int readMlVolt(adc_channel_t channel);

private:
    AdcOneshot(const AdcOneshot &) = delete;
    AdcOneshot & operator=(const AdcOneshot &) = delete;

    adc_oneshot_unit_handle_t _adc_handle; // Handle for ADC hardware unit

    adc_unit_t _unit; // Stores the ADC unit
    std::map<adc_channel_t, adc_oneshot_chan_cfg_t> channel_configs; // Config map per channel
    std::map<std::pair<adc_atten_t, adc_bitwidth_t>, adc_cali_handle_t> cali_handles; // Calibration handles

    void create_calibration(adc_atten_t atten, adc_bitwidth_t bitwidth); // Create calibration for specific settings
};

} // idf

#endif // __cpp_exceptions
