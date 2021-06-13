cmake_minimum_required(VERSION 3.14)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics network audio)

add_executable(Lab1 main.cpp Particle.hpp Space.cpp Space.hpp Vector.hpp config.hpp demos.hpp demos.cpp)

target_link_libraries(Lab1 OpenGL::GL)
target_link_libraries(Lab1 ${OPENGL_LIBRARIES} sfml-graphics sfml-window sfml-system)