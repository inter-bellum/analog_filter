cmake_minimum_required(VERSION 3.18)
project(test_analog_filter)

set(SRC main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(test_filter main.cpp)

target_include_directories(test_filter PRIVATE
    ../include)