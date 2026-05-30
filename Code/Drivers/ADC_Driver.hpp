#ifndef ADC_DRIVER_HPP
#define ADC_DRIVER_HPP

#include <cstdint>

class ADCDriver {
public:
    ADCDriver();
    void Init();
    uint16_t GetValue();
    float GetVoltage();
    
private:
    volatile uint32_t m_adcValue;
};

#endif