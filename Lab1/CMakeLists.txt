cmake_minimum_required(VERSION 3.14)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab1
        integer.cpp
        integer.hpp
        test.cpp)
