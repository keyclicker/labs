cmake_minimum_required(VERSION 3.15)
project(Lab3С)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)
add_executable(bench benchmark.cpp)
target_link_libraries(bench benchmark::benchmark)

add_executable(demo main.cpp)
target_link_libraries(demo pthread)