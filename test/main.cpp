#include <cmath>
#include <thread>
#include <chrono>

#include "EMA.hpp"
#include "MA.hpp"
#include "no_filter.hpp"
#include "Pot.hpp"

uint16_t cycles = 0;

int
read(uint8_t pin)
{
    return ((cycles++ % 100) > 50) * 1023;
}

Pot<EMA> p{0.1, read};
Pot<MA> p2{0.1, read};
Pot<no_filter> p3{0.1, read};

int
main(int argc, char** argv)
{
    using namespace std::chrono_literals;
    p.initialize(0, 0);

    while (true) {
        if (p.update())
            std::cout << "Value is " << p.read() << std::endl;

        std::this_thread::sleep_for(10ms);
    }
}