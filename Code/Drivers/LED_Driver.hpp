#ifndef LED_DRIVER_HPP
#define LED_DRIVER_HPP

#include <cstdint>

class LEDDriver {
public:
    void Init();
    void SetLED(uint8_t index, bool state);
    void SetAll(bool state);
    void SetCount(uint8_t count);
    
    static constexpr uint8_t LED_COUNT = 4;
};

#endif