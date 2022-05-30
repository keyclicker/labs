#include "../Data.hpp"
#include "../des.cpp"
#include <gtest/gtest.h>

TEST(DesTest, InitialPermutation) {
  auto block = Data::fromHexString("675a69675e5a6b5a");
  auto ipBlock = permutation(block, ip, sizeof(ip));

  EXPECT_EQ("ffb2194d004df6fb", ipBlock.toHexString());
}

TEST(DesTest, KeyDeriving) {
  auto key = Data::fromHexString("5b5a57676a56676e");

  auto pkey = permutation(key, kd, 56);
  
  auto lkey = pkey.sliceBits(0, 28);
  auto rkey = pkey.sliceBits(28, 56);

  EXPECT_EQ("ffb2194d", lkey.toHexString());
  EXPECT_EQ("004df6fb", rkey.toHexString());
}