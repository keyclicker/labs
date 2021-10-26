cmake_minimum_required(VERSION 3.16)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DBOOST_USE_WINDOWS_H -DWIN32_LEAN_AND_MEAN)


set(Boost_THREADAPI win32)
set(Boost_COMPILER "-gcc")
set(Boost_INCLUDE_DIR C:/boost/boost/include/boost-1_66)
set(Boost_LIBRARY_DIR C:/boost/boost/lib)

#set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(Lab1 main.cpp)
target_link_libraries(Lab1 ${Boost_LIBRARIES})
