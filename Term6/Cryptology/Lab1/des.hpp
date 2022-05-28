#pragma once

#include <iostream>
#include "Data.hpp"

constexpr uint8_t ip[] = {
  58, 50, 42, 34, 26, 18, 10, 2,
  60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6,
  64, 56, 48, 40, 32, 24, 16, 8,
  57, 49, 41, 33, 25, 17, 9,  1,
  59, 51, 43, 35, 27, 19, 11, 3,
  61, 53, 45, 37, 29, 21, 13, 5,
  63, 55, 47, 39, 31, 23, 15, 7 
};

constexpr uint8_t ipr[] = {   
  40, 8, 48, 16, 56, 24, 64, 32,
  39, 7, 47, 15, 55, 23, 63, 31,
  38, 6, 46, 14, 54, 22, 62, 30,
  37, 5, 45, 13, 53, 21, 61, 29,
  36, 4, 44, 12, 52, 20, 60, 28,
  35, 3, 43, 11, 51, 19, 59, 27,
  34, 2, 42, 10, 50, 18, 58, 26,
  33, 1, 41, 9,  49, 17, 57, 25
};

// Expansion D-box Table
constexpr uint8_t ed[] = { 
32, 1,  2,  3,  4,  5,  4,   5,
6,  7,  8,  9,  8,  9,  10, 11,
12, 13, 12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21, 20, 21,
22, 23, 24, 25, 24, 25, 26, 27,
28, 29, 28, 29, 30, 31, 32, 1 
};

// Key discarding table
constexpr uint8_t kd[] = {
  57, 49, 41, 33, 25, 17, 9,  1,
  58, 50, 42, 34, 26, 18, 10, 2,
  59, 51, 43, 35, 27, 19, 11, 3,
  60, 52, 44, 36, 63, 55, 47, 39,
  31, 23, 15, 7,  62, 54, 46, 38,
  30, 22, 14, 6,  61, 53, 45, 37,
  29, 21, 13, 5,  28, 20, 12, 4
};

Data permutation(const Data &block, 
     const uint8_t *permutation, uint8_t size) {
  auto result = Data::Bits(size);
  for (int i = 0; i < size; i++) {
    result.setBit(i, block.getBit(ip[i] - 1));
  }
  return result;
}

Data F(const Data &block, const Data &key) {
  auto edBlock = permutation(block, ed, 48);


  auto result = Data::Bits(32);
  return result;
}

Data desEncryptBlock(const Data &block, const Data &key) {
  std::cout << "Encrypting block: " << block.toHexString() << std::endl;

  auto ip_block = permutation(block, ip, 64);

  std::cout << "initial permutation: " << ip_block.toHexString() << std::endl;

  auto left = ip_block.sliceBytes(0, 4);
  auto right = ip_block.sliceBytes(4, 8);

  std::cout << "left: " << left.toHexString() << std::endl;
  std::cout << "right: " << right.toHexString() << std::endl;

  return Data::fromString("keyclick");
}

