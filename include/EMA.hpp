#pragma once

#ifdef TEST_LOCAL
#include <cstdint>
#endif

#include "filter.hpp"

template <typename T>
class EMA : public Filter<T> {
    using idx_t = uint32_t;
public:
    EMA(float num_values);
    ~EMA() = default;

    T
    update(T new_value);

    T
    get();
private:
    T
    calc(T new_value);

    idx_t idx;
    T out;
    T prev;
};

template <typename T>
EMA<T>::EMA(float num_values)
    : Filter<T>(num_values)
{}

template <typename T>
T
EMA<T>::calc(T new_value)
{
    return (this->scaling * new_value) + ((1 - this->scaling) * prev);
}

template <typename T>
T
EMA<T>::update(T new_value)
{
    prev = out = this->calc(new_value);
    return out;
}

template <typename T>
T
EMA<T>::get()
{
    return out;
}