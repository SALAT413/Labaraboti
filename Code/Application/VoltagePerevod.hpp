#ifndef VOLTAGE_PEREVOD_HPP
#define VOLTAGE_PEREVOD_HPP

#include <cstdint>

class VoltagePerevod {
public:
    static float Convert(uint16_t adcCode) {
        const uint32_t ADC_RESOLUTION = 4095;
        const float ADC_REF_VOLTAGE = 3.3f;
        return (float)adcCode * ADC_REF_VOLTAGE / ADC_RESOLUTION;
    }
};
#endif