#include "MeasurementTask.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "tim2registers.hpp"
#include "rccregisters.hpp"

static volatile bool measurementReady = false;
uint8_t measurementCounter = 0;

extern "C" void TIM2_IRQHandler(void) {
    if (TIM2::SR::UIF::InterruptPending::IsSet()) {
        TIM2::SR::UIF::Set(0);
        measurementReady = true;
    }
}

void MeasurementTask::InitTimer() {
    RCC::APB1ENR::TIM2EN::Enable::Set();
    TIM2::PSC::Set(16000 - 1);
    TIM2::ARR::Write(50 - 1);
    TIM2::SR::UIF::Set(0);
    TIM2::CNT::Set(0);
    TIM2::DIER::UIE::Enable::Set();
    
    #define NVIC_ISER0 (*(volatile uint32_t*)0xE000E100U)
    NVIC_ISER0 |= (1 << 28);
    
    TIM2::CR1::CEN::Enable::Set();
}

MeasurementTask::MeasurementTask(ADCDriver& adc, FilteredVoltage& filter, LedMailBox& ledMailBox, UartMailBox& uartMailBox)
    : m_adc(adc), m_filter(filter), m_ledMailBox(ledMailBox), m_uartMailBox(uartMailBox) {}

void MeasurementTask::Execute() {
    m_adc.Init();
    InitTimer();
    
    for (;;) {
        if (measurementReady) {
            measurementReady = false;
            measurementCounter++;
            
            if (measurementCounter >= 2) {
                measurementCounter = 0;
                
                float rawVoltage = m_adc.GetVoltage();
                ProcessVoltage(rawVoltage);
                
                float filteredVoltage = m_filter.GetValue();
                
                m_ledMailBox.Send(filteredVoltage);
                m_uartMailBox.Send(filteredVoltage);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void MeasurementTask::ProcessVoltage(float rawVoltage) {
    m_filter.Update(rawVoltage);
}