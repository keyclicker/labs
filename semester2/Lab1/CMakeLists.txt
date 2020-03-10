cmake_minimum_required(VERSION 3.15)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)
add_executable(test benchmark.cpp Database.hpp Message.cpp Message.hpp Time.hpp)
target_link_libraries(test benchmark::benchmark)

add_executable(Lab1 main.cpp Database.hpp Message.cpp Message.hpp Time.hpp interactive.hpp interactive.cpp)