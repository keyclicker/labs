cmake_minimum_required(VERSION 3.22)
project(DES)


find_package(OpenSSL REQUIRED)
add_executable(main main.cpp Data.cpp des.cpp)
target_link_libraries(main OpenSSL::Crypto)


enable_testing()
find_package(GTest REQUIRED)
add_executable(tests test/Data.cpp Data.cpp)
target_link_libraries(tests GTest::gtest GTest::gtest_main OpenSSL::Crypto)

add_test(AllTests tests)