cmake_minimum_required(VERSION 3.17)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(Lab1 main.cpp)
add_executable(test test.cpp)

target_link_libraries(test GTest::GTest GTest::Main)

#add_test(AllTestsInFoo Lab1)