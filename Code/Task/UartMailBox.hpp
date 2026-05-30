#ifndef UART_MAIL_BOX_HPP
#define UART_MAIL_BOX_HPP

#include "FreeRTOS.h"
#include "queue.h"

#define UART_MAILBOX_SIZE 10

typedef float UartMailBoxDataType;

class UartMailBox {
public:
    void Create() {
        if (m_handle == nullptr) {
            m_handle = xQueueCreate(UART_MAILBOX_SIZE, sizeof(UartMailBoxDataType));
        }
    }
    
    bool Send(const UartMailBoxDataType& value, TickType_t timeout = 0) {
        if (m_handle == nullptr) return false;
        return xQueueSend(m_handle, &value, timeout) == pdPASS;
    }
    
    bool Receive(UartMailBoxDataType& value, TickType_t timeout = pdMS_TO_TICKS(100)) {
        if (m_handle == nullptr) return false;
        return xQueueReceive(m_handle, &value, timeout) == pdPASS;
    }
    
private:
    QueueHandle_t m_handle = nullptr;
};

#endif