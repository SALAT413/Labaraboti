#ifndef USART_DRIVER_HPP
#define USART_DRIVER_HPP

#include <cstdint>
#include <cstdarg>
#include <cstdio>

class USART2Driver {
public:
    void Init(uint32_t baudrate);
    void SendChar(char c);
    void SendString(const char* str);
};

#endif