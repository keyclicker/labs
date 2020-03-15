cmake_minimum_required(VERSION 3.15)
project(A)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)
add_executable(bench benchmark.cpp Container.hpp Vector.hpp Array.hpp List.hpp)
target_link_libraries(bench benchmark::benchmark)

add_executable(A main.cpp Container.hpp Vector.hpp Array.hpp List.hpp)