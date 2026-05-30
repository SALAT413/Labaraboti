#include "LEDIndicatorTask.hpp"
#include "FreeRTOS.h"
#include "task.h"

LEDIndicatorTask::LEDIndicatorTask(LedMailBox& ledMailBox, VoltageRangeCalculator& voltageRange, LEDDriver& ledDriver)
    : m_ledMailBox(ledMailBox), m_voltageRange(voltageRange), m_ledDriver(ledDriver) {}

void LEDIndicatorTask::Execute() {
    m_ledDriver.Init();
    float voltage = 0.0f;
    
    for (;;) {
        if (m_ledMailBox.Receive(voltage, portMAX_DELAY)) {
            UpdateLEDs(voltage);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void LEDIndicatorTask::UpdateLEDs(float voltage) {
    const float VOLTAGE_MAX = 3.3f;
    VoltageRange range = m_voltageRange.Calculate(voltage, VOLTAGE_MAX);
    uint8_t ledCount = m_voltageRange.GetLedCount(range);
    m_ledDriver.SetCount(ledCount);
}