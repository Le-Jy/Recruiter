#pragma once

/**
 * @brief Start the line follower sensor, will start the adc and read the value of the sensor
*/
void line_follower_sensor(adc_unit_t adc_unit, adc_channel_t adc_channel, idf::AdcOneshot& adc, std::mutex& adcMutex);
