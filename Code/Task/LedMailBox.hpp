#ifndef LED_MAIL_BOX_HPP
#define LED_MAIL_BOX_HPP

#include "FreeRTOS.h"
#include "queue.h"

#define LED_MAILBOX_SIZE 10

typedef float LedMailBoxDataType;

class LedMailBox {
public:
    void Create() {
        if (m_handle == nullptr) {
            m_handle = xQueueCreate(LED_MAILBOX_SIZE, sizeof(LedMailBoxDataType));
        }
    }
    
    bool Send(const LedMailBoxDataType& value, TickType_t timeout = 0) {
        if (m_handle == nullptr) return false;
        return xQueueSend(m_handle, &value, timeout) == pdPASS;
    }
    
    bool Receive(LedMailBoxDataType& value, TickType_t timeout = portMAX_DELAY) {
        if (m_handle == nullptr) return false;
        return xQueueReceive(m_handle, &value, timeout) == pdPASS;
    }
    
private:
    QueueHandle_t m_handle = nullptr;
};

#endif