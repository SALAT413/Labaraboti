#ifndef VOLTAGE_RANGE_HPP
#define VOLTAGE_RANGE_HPP

#include <cstdint>

enum class VoltageRange : uint8_t {
    LEVEL_0 = 0,
    LEVEL_1 = 1,
    LEVEL_2 = 2,
    LEVEL_3 = 3
};

class VoltageRangeCalculator {
public:
    VoltageRange Calculate(float voltage, float maxVoltage);
    uint8_t GetLedCount(VoltageRange range);
};

#endif