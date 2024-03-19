#pragma once
#include <cstdint>

#include "filter.hpp"

template <typename T>
class MA : public Filter<T> {
    using idx_t = uint32_t;
public:
    MA(float num_values);
    ~MA();

    T
    update(T new_value);

    T
    get();
private:
    T 
    calc(T new_value);

    idx_t idx;
    idx_t num_values;
    T filtered_value;
    T values[];
};

template <typename T>
MA<T>::MA(float num_values)
    : Filter<T>(num_values * 100), values(new T[static_cast<idx_t>(num_values * 100)])
{}

template <typename T>
MA<T>::~MA()
{
    delete this->values;
}

template <typename T>
T
MA<T>::calc(T new_value)
{
    float sum = 0;
    for (idx_t i = 0; i < this->num_values; i++){
        sum += values[i];
    }
    return sum / this->scaling;
}

template <typename T>
T
MA<T>::get()
{
    return this->filtered_value;
}

template <typename T>
T
MA<T>::update(T new_value)
{
    values[idx++] = new_value;
    if (idx > this->num_values) {
        idx = 0;
    }

    this->filtered_value = this->calc(0);
    return this->filtered_value;
}