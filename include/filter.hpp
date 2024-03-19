#pragma once

#include <cstdint>

template <typename T>
class Filter {
public:
    Filter(float scaling);
    virtual ~Filter() = default;

    virtual T
    update(T new_value) = 0;

    virtual T
    get() = 0;
protected:
    virtual T
    calc(T new_value) = 0;

    const float scaling = 0;
};

template <typename T>
Filter<T>::Filter(float scaling)
    : scaling(scaling)
{}