#ifndef LED_INDICATOR_TASK_HPP
#define LED_INDICATOR_TASK_HPP

#include "LedMailBox.hpp"
#include "VoltageRange.hpp"
#include "LED_Driver.hpp"

class LEDIndicatorTask {
public:
    LEDIndicatorTask(LedMailBox& ledMailBox, VoltageRangeCalculator& voltageRange, LEDDriver& ledDriver);
    void Execute();
    
private:
    LedMailBox& m_ledMailBox;
    VoltageRangeCalculator& m_voltageRange;
    LEDDriver& m_ledDriver;
    
    void UpdateLEDs(float voltage);
};

#endif