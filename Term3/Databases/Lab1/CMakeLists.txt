cmake_minimum_required(VERSION 3.17)
project(Lab1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab1 src/main.c include/comment.h include/database.h src/database.c include/defs.h)