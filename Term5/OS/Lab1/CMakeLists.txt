cmake_minimum_required(VERSION 3.16)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)
find_package(SFML 2.5.1 COMPONENTS window REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(Lab1 main.cpp Config.hpp)
target_link_libraries(Lab1 ${Boost_LIBRARIES} sfml-window)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Lab1 Threads::Threads)

add_executable(test supplementary/test.cpp)