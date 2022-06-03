cmake_minimum_required(VERSION 3.22)
project(DES)

set (CMAKE_CXX_STANDARD 17)

set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@3/")

find_package(OpenSSL REQUIRED)
add_executable(main main.cpp des.cpp des.cpp data.cpp)
target_link_libraries(main OpenSSL::Crypto)

#enable_testing()
#find_package(GTest REQUIRED)
#add_executable(tests test/Data.cpp test/des_block.cpp)
#target_link_libraries(tests GTest::gtest GTest::gtest_main OpenSSL::Crypto)
#
#add_test(AllTests tests)