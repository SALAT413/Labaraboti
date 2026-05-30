#include "BluetoothReporterTask.hpp"
#include "FreeRTOS.h"
#include "task.h"

BluetoothReporterTask::BluetoothReporterTask(UartMailBox& uartMailBox, Formatter& formatter, USART2Driver& usartDriver)
    : m_uartMailBox(uartMailBox), m_formatter(formatter), m_usartDriver(usartDriver) {}

void BluetoothReporterTask::Execute() {
    float voltage = 0.0f;
    
    for (;;) {
        if (m_uartMailBox.Receive(voltage, pdMS_TO_TICKS(100))) {
            ReportVoltage(voltage);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void BluetoothReporterTask::ReportVoltage(float voltage) {
    char buffer[128];
    m_formatter.Format(voltage, buffer, sizeof(buffer));
    m_usartDriver.SendString(buffer);
}