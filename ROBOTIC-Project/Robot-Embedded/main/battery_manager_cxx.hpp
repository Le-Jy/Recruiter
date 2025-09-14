#pragma once

/**
* @brief Start the battery manager, will start the adc, check if the battery is low and play a sound
*/
void batteryManager(adc_unit_t adc_unit, adc_channel_t adc_channel, idf::AdcOneshot& adc, std::mutex& adcMutex);
