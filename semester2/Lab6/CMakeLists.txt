cmake_minimum_required(VERSION 3.16)
project(Lab6)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo main.cpp)
add_executable(interactive interactive.cpp)

find_package(benchmark REQUIRED)
add_executable(bench benchmark.cpp)
target_link_libraries(bench benchmark::benchmark)