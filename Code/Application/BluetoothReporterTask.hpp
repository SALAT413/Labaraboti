#ifndef BLUETOOTH_REPORTER_TASK_HPP
#define BLUETOOTH_REPORTER_TASK_HPP

#include "UartMailBox.hpp"
#include "Formatter.hpp"
#include "USART_Driver.hpp"

class BluetoothReporterTask {
public:
    BluetoothReporterTask(UartMailBox& uartMailBox, Formatter& formatter, USART2Driver& usartDriver);
    void Execute();
    
private:
    UartMailBox& m_uartMailBox;
    Formatter& m_formatter;
    USART2Driver& m_usartDriver;
    
    void ReportVoltage(float voltage);
};

#endif