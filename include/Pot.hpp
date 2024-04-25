#pragma once 

#ifdef ARDUINO
#include "Arduino.h"
#else
#include <cstdint>
#include <iostream>

class serial_t {
public:
    serial_t() = default;
    ~serial_t() = default;

    template <typename T>
    void
    print(T& arg)
    {
        std::cout << arg;
    }

    template <typename T>
    void
    println(T& arg)
    {
        std::cout << arg << std::endl;
    }

    void
    println()
    {
        std::cout << std::endl;
    }
private:
};

serial_t Serial;
#endif

#include "filter.hpp"
#include "hysteresis.hpp"

#define HISTORY_SIZE  100

template <template <typename> class filter_t, typename value_t = uint16_t, uint8_t MaxIn = 10, uint8_t MaxOut = 7>
class Pot {
    using read_func = value_t(*)(int);

    read_func read_value;
    uint8_t analogPin;
    uint8_t index;
    filter_t<value_t> filter;
    hysteresis<value_t, MaxIn, MaxOut> hyst;
    value_t last_value;

public:

#ifdef ARDUINO
    Pot(float filter_length_or_scaling);
#endif
    Pot(float filter_length_or_scaling, read_func read);
    ~Pot() = default;

    void 
    initialize(uint8_t analog_in, uint8_t index);

    bool
    update();

    bool
    update(value_t value);

    value_t 
    read();

    uint16_t 
    getValue();

    uint8_t 
    getPin();

    void
    debugPlot(bool endl);
};

#ifdef ARDUINO
template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
Pot<filter_t, value_t, MaxIn, MaxOut>::Pot(float filter_length_or_scaling)
    : filter(filter_length_or_scaling), read_value(analogRead)
{}
#endif

template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
Pot<filter_t, value_t, MaxIn, MaxOut>::Pot(float filter_length_or_scaling, read_func read)
    : filter(filter_length_or_scaling), read_value(read)
{}

template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
void
Pot<filter_t, value_t, MaxIn, MaxOut>::initialize(uint8_t analogPin, uint8_t index)
{
    this->analogPin = analogPin;
    this->index = index;
}

template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
bool 
Pot<filter_t, value_t, MaxIn, MaxOut>::update()
{
    uint16_t read_val = read_value(analogPin);

    if (hyst.update(filter.update(read_val))) {
        last_value = hyst.get();
        return true;
    }

    return false;
}

template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
bool 
Pot<filter_t, value_t, MaxIn, MaxOut>::update(value_t value)
{
    if (hyst.update(filter.update(value))) {
        last_value = hyst.get();
        return true;
    }

    return false;
}

template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
value_t 
Pot<filter_t, value_t, MaxIn, MaxOut>::read()
{
    return last_value;
}

template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
uint16_t 
Pot<filter_t, value_t, MaxIn, MaxOut>::getValue()
{
    return filter.get();
}

template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
uint8_t
Pot<filter_t, value_t, MaxIn, MaxOut>::getPin()
{
    return this->analogPin;
}

template <template <typename> class filter_t, typename value_t, uint8_t MaxIn, uint8_t MaxOut>
void
Pot<filter_t, value_t, MaxIn, MaxOut>::debugPlot(bool endl)
{
    Serial.print("pin");
    Serial.print(analogPin);
    Serial.print(":");
    Serial.print(last_value);
    if (endl) {
        Serial.println();
    } else {
        Serial.print(",");
    }
}
