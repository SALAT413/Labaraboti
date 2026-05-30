#ifndef MEASUREMENT_TASK_HPP
#define MEASUREMENT_TASK_HPP

#include "ADC_Driver.hpp"
#include "FilteredVoltage.hpp"
#include "LedMailBox.hpp"
#include "UartMailBox.hpp"

class MeasurementTask {
public:
    MeasurementTask(ADCDriver& adc, FilteredVoltage& filter, LedMailBox& ledMailBox, UartMailBox& uartMailBox);
    void Execute();
    
private:
    ADCDriver& m_adc;
    FilteredVoltage& m_filter;
    LedMailBox& m_ledMailBox;
    UartMailBox& m_uartMailBox;
    
    void ProcessVoltage(float rawVoltage);
    void InitTimer();
};

#endif