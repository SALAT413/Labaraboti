#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <cstdio>

class Formatter {
public:
    void Format(float voltage, char* buffer, size_t bufferSize) {
        const char* OUTPUT_FORMAT = "Voltage: %.3f V\r\n";
        snprintf(buffer, bufferSize, OUTPUT_FORMAT, (double)voltage);
    }
};

#endif