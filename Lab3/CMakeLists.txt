cmake_minimum_required(VERSION 3.15)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab3 main.cpp GraphBuilder.cpp GraphBuilder.hpp fourier.hpp)

find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics network audio)

link_directories(${SFML_LIBRARY_DIRS})
include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(Lab3 ${OPENGL_LIBRARIES} sfml-graphics sfml-window sfml-system)