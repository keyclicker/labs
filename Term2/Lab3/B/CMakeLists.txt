cmake_minimum_required(VERSION 3.15)
project(B)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)
add_executable(bench benchmark.cpp)
target_link_libraries(bench benchmark::benchmark)

add_executable(demo main.cpp Lab1/interactive.cpp Lab1/Message.cpp Lab1/)
add_executable(interactive Lab1/main.cpp Lab1/interactive.cpp Lab1/Message.cpp Lab1/)
