cmake_minimum_required(VERSION 3.16)
project(Lab5)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.71 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(Lab5 main.cpp)

target_link_libraries(Lab5 ${Boost_LIBRARIES})