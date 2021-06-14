cmake_minimum_required(VERSION 3.14)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics network audio)
find_package(GTest REQUIRED)

add_executable(Lab1 src/main.cpp include/Particle.hpp src/Space.cpp include/Space.hpp include/Vector.hpp include/Config.hpp include/Demos.hpp src/Demos.cpp src/Random.cpp include/HSV.hpp)
add_executable(test tests/test.cpp src/Space.cpp)

target_link_libraries(Lab1 OpenGL::GL)
target_link_libraries(Lab1 ${OPENGL_LIBRARIES} sfml-graphics sfml-window sfml-system)
target_link_libraries(test GTest::GTest GTest::Main)