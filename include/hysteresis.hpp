#pragma once

#ifndef TEST_LOCAL
#include <Arduino.h>
#else
#include <cstdint>
#include <iostream>
#include <cmath>
#endif

template <typename T>
constexpr T ipow(T num, unsigned int pow)
{
    return (pow >= sizeof(unsigned int)*8) ? 0 :
        pow == 0 ? 1 : num * ipow(num, pow-1);
}

template <typename In_t, uint8_t In, uint8_t Out>
class hysteresis {
public:
    hysteresis() = default;
    ~hysteresis() = default;

    bool
    update(In_t in);

    In_t
    get();
private:
    constexpr static uint8_t ratio = In - Out;
    constexpr static float f_margin = 0.8;
    constexpr static In_t step = ipow(2, ratio);
    constexpr static In_t max_v = f_margin * step;
    constexpr static In_t min_v = step - max_v;

    In_t value;
};

template <typename In_t, uint8_t In, uint8_t Out>
bool
hysteresis<In_t, In, Out>::update(In_t in)
{
    int prev_full = this->value * step;
    int diff = in - prev_full;
    if (diff >= max_v) {
        this->value = (in + (step - max_v)) / step;
        return true;
    } else if (diff <= -max_v) {
        this->value = in / step;
        return true;
    }
    
    return false;
}

template <typename In_t, uint8_t In, uint8_t Out>
In_t
hysteresis<In_t, In, Out>::get()
{
    return this->value;
}