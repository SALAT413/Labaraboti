#ifndef FILTERED_VOLTAGE_HPP
#define FILTERED_VOLTAGE_HPP

class FilteredVoltage {
public:
    FilteredVoltage(float tau);
    void Update(float rawVoltage);
    float GetValue() const;
    
private:
    float m_tau;
    float m_filteredValue;
    bool m_firstSample;
};

#endif