# analog_filter repo
This repo provides an implementation for a processed analog read flow. The analog values are read through the arduino function, passed into a filter (selectable with template arguments), and then processed with hysteresis to reduce jitter.
It was made for specifically using analog inputs as midi signals, but any downsampling can be done.

## how it works
The main class in this flow is Pot. It contains the analogReads, the filter and the hysteresis. It has a couple of template parameters that can be finetuned to fit your needs:

template <template <typename> class filter_t, typename value_t = uint16_t, uint8_t MaxIn = 10, uint8_t MaxOut = 7>

Let's break this down.

template <typename> class filter_t: The filter class, which itself takes a typename for its input type as a parameter.
value_t = uint16_t: The type of the input value. Should be big enough to actually hold the read value. The default is set to uint16 (for arduino/teensy built-in analogRead)
MaxIn = 10: The max number of bits used for the input value (10 on arduino/teensy built-in analogRead)
MaxOut = 7: The max number of bits to be used for the output value (7 is for MIDI)

## to extend
New filters can be added as subclasses of the filter class. See the EMA implementation for more details. If you override the update, get, and calc functions, it should work. You don't even need to use templated classes to extend the filter if you don't plan on changing the min/max values. You can do the following:
```
class new_filter : public Filter<uint16_t> {
public:
    new_filter(float init, uint32_t _another_var) : Filter<uint16_t>(init), another_var(_another_var) {}
    ~new_filter() = default;

    uint16_t
    get();

    uint16_t 
    update(uint16_t new_val);

private:
    uint32_t another_var;

    uint16_t 
    calc(uint16_t new_val);
};
```

It's not required to derive from the Filter class to use this code, but it helps to make sure you got everything, since the compiler will swear at you if you missed a method or used the wrong type.