cmake_minimum_required(VERSION 3.14)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab5 main.cpp lab.hpp lab.cpp polish.hpp polish.cpp)

target_include_directories(Lab5 PUBLIC | PRIVATE <dir>)