#include "LED_Driver.hpp"
#include "rccregisters.hpp"
#include "gpioaregisters.hpp"
#include "gpiocregisters.hpp"

void LEDDriver::Init() {
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    RCC::AHB1ENR::GPIOCEN::Enable::Set();
    GPIOA::MODER::MODER5::Output::Set();
    GPIOC::MODER::MODER5::Output::Set();
    GPIOC::MODER::MODER8::Output::Set();
    GPIOC::MODER::MODER9::Output::Set();
    SetAll(false);
}

void LEDDriver::SetLED(uint8_t index, bool state) {
    switch (index) {
        case 0:
            if (state) GPIOA::ODR::ODR5::High::Set();
            else GPIOA::ODR::ODR5::Low::Set();
            break;
        case 1:
            if (state) GPIOC::ODR::ODR9::High::Set();
            else GPIOC::ODR::ODR9::Low::Set();
            break;
        case 2:
            if (state) GPIOC::ODR::ODR8::High::Set();
            else GPIOC::ODR::ODR8::Low::Set();
            break;
        case 3:
            if (state) GPIOC::ODR::ODR5::High::Set();
            else GPIOC::ODR::ODR5::Low::Set();
            break;
    }
}

void LEDDriver::SetAll(bool state) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        SetLED(i, state);
    }
}

void LEDDriver::SetCount(uint8_t count) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        SetLED(i, i < count);
    }
}