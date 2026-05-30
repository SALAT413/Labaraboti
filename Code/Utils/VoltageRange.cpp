#include "VoltageRange.hpp"

static const float LED_LEVEL_1 = 0.25f;
static const float LED_LEVEL_2 = 0.50f;
static const float LED_LEVEL_3 = 0.75f;

VoltageRange VoltageRangeCalculator::Calculate(float voltage, float maxVoltage) {
    float percentage = voltage / maxVoltage;
    
    if (percentage >= LED_LEVEL_3) {
        return VoltageRange::LEVEL_3;
    } else if (percentage >= LED_LEVEL_2) {
        return VoltageRange::LEVEL_2;
    } else if (percentage >= LED_LEVEL_1) {
        return VoltageRange::LEVEL_1;
    } else {
        return VoltageRange::LEVEL_0;
    }
}

uint8_t VoltageRangeCalculator::GetLedCount(VoltageRange range) {
    switch (range) {
        case VoltageRange::LEVEL_3: return 4;
        case VoltageRange::LEVEL_2: return 3;
        case VoltageRange::LEVEL_1: return 2;
        default: return 1;
    }
}