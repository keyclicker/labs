cmake_minimum_required(VERSION 3.17)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)


find_package(Boost 1.71 REQUIRED)
find_package(GTest REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics network audio)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SFML_INCLUDE_DIRS})

link_directories(${SFML_LIBRARY_DIRS})

add_executable(task2 src/main.cpp src/FunctionBuilder/FunctionBuilder.cpp)
add_executable(test tests/graph_test.cpp tests/shape_test.cpp)

target_link_libraries(test GTest::GTest GTest::Main)
target_link_libraries(task2 ${OPENGL_LIBRARIES} sfml-graphics sfml-window sfml-system)