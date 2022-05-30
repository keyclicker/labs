cmake_minimum_required(VERSION 3.22)
project(DES)

set (CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
add_executable(main main.cpp Data.cpp des.cpp)
target_link_libraries(main OpenSSL::Crypto)

# add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests test/Data.cpp test/des.cpp)
target_link_libraries(tests GTest::gtest GTest::gtest_main OpenSSL::Crypto)

add_test(AllTests tests)