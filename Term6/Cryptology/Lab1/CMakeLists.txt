cmake_minimum_required(VERSION 3.23)
project(DES)


find_package(OpenSSL REQUIRED)
add_executable(main main.cpp Data.cpp des.cpp)
target_link_libraries(main OpenSSL::Crypto)


# enable_testing()
find_package(GTest REQUIRED)
add_executable(test test/Data.cpp)
target_link_libraries(test GTest::gtest GTest::gtest_main)

# add_test(AllTests test)