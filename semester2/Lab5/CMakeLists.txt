cmake_minimum_required(VERSION 3.16)
project(Lab5)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.71 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(interactive interactive.cpp)
add_executable(demo main.cpp)

target_link_libraries(interactive ${Boost_LIBRARIES})
target_link_libraries(demo ${Boost_LIBRARIES})

find_package(benchmark REQUIRED)
add_executable(bench benchmark.cpp)
target_link_libraries(bench benchmark::benchmark)