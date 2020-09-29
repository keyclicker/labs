cmake_minimum_required(VERSION 3.17)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)


find_package(Boost 1.71 REQUIRED)
find_package(GTest REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(Lab1 src/main.cpp)
add_executable(test tests/graph_test.cpp)

target_link_libraries(test GTest::GTest GTest::Main)
target_link_libraries(Lab1 ${Boost_LIBRARIES})