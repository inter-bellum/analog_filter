#include "filter.hpp"

template <typename T>
class no_filter : public Filter<T>
{
public:
    no_filter(float unused) : Filter<T>(0), value(0) {}
    ~no_filter() {}

    T
    update(T new_value) { return calc(new_value); };

    T
    get() { return value; };
protected:
    T
    calc(T new_value) { value = new_value; return new_value; };

    T value;
};