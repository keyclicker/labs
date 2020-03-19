cmake_minimum_required(VERSION 3.15)
project(B)

set(CMAKE_CXX_STANDARD 17)

add_executable(n16 Journal.hpp journal.cpp)
add_executable(n20 Set.hpp set.cpp)

add_executable(n30 shooter.cpp)

find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics network audio)

link_directories(${SFML_LIBRARY_DIRS})
include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(n30 ${OPENGL_LIBRARIES} sfml-graphics sfml-window sfml-system)