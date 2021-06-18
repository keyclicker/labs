cmake_minimum_required(VERSION 3.19)
project(Lab3a)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
add_executable(test test.cpp)
target_link_libraries(test GTest::GTest GTest::Main)

find_package(benchmark REQUIRED)
add_executable(bench benchmark.cpp)
target_link_libraries(bench benchmark::benchmark)

add_executable(Lab3a main.cpp Graph.hpp test.cpp benchmark.cpp)

target_link_libraries(Lab3a pthread)