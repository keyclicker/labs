cmake_minimum_required(VERSION 3.17)
project(Lab5)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)
add_executable(bench benchmark.cpp)
target_link_libraries(bench benchmark::benchmark)

add_executable(Lab5 main.cpp)

