#include "FilteredVoltage.hpp"

FilteredVoltage::FilteredVoltage(float tau) 
    : m_tau(tau), m_filteredValue(0.0f), m_firstSample(true) {}

void FilteredVoltage::Update(float rawVoltage) {
    if (m_firstSample) {
        m_filteredValue = rawVoltage;
        m_firstSample = false;
    } else {
        m_filteredValue = m_filteredValue + (rawVoltage - m_filteredValue) * m_tau;
    }
}

float FilteredVoltage::GetValue() const {
    return m_filteredValue;
}