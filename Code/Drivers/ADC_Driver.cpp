#include "ADC_Driver.hpp"
#include "adc1registers.hpp"
#include "adccommonregisters.hpp"
#include "dma2registers.hpp"
#include "rccregisters.hpp"
#include "gpioaregisters.hpp"

ADCDriver::ADCDriver() : m_adcValue(0) {}

void ADCDriver::Init() {
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    RCC::APB2ENR::ADC1EN::Enable::Set();
    RCC::AHB1ENR::DMA2EN::Enable::Set();
    GPIOA::MODER::MODER0::Analog::Set();
    
    DMA2::S0CR::EN::Value0::Set();
    DMA2::S0CR::CHSEL::Value0::Set();
    DMA2::S0CR::CIRC::Value1::Set();
    DMA2::S0CR::MSIZE::Value2::Set();
    DMA2::S0CR::PSIZE::Value2::Set();
    DMA2::S0CR::DIR::Value0::Set();
    DMA2::S0PAR::Write(ADC1::DR::Address);
    DMA2::S0M0AR::Write(reinterpret_cast<uint32_t>(&m_adcValue));
    DMA2::S0NDTR::Write(1);
    DMA2::S0CR::EN::Value1::Set();
    
    ADC1::CR1::RES::Bits12::Set();
    ADC1::CR1::SCAN::Enable::Set();
    ADC1::CR2::CONT::ContinuousConversion::Set();
    ADC1::CR2::DMA::Enable::Set();
    ADC1::CR2::DDS::DMARequest::Set();
    ADC1::SQR1::L::Conversions1::Set();
    ADC1::SQR3::SQ1::Channel0::Set();
    ADC1::SMPR2::SMP0::Cycles84::Set();
    
    ADC1::CR2::ADON::Enable::Set();
    for (int i = 0; i < 1000; i++);
    ADC1::CR2::SWSTART::On::Set();
}

uint16_t ADCDriver::GetValue() {
    return static_cast<uint16_t>(m_adcValue & 0x0FFF);
}

float ADCDriver::GetVoltage() {
    const uint32_t ADC_RESOLUTION = 4095;
    const float ADC_REF_VOLTAGE = 3.3f;
    return (float)GetValue() * ADC_REF_VOLTAGE / ADC_RESOLUTION;
}