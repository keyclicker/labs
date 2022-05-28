#include "../Data.hpp"
#include <gtest/gtest.h>

TEST(DataTest, Bits) {
  auto data = Data::Bits(8);
  EXPECT_EQ(8, data.getBitSize());
  EXPECT_EQ(1, data.getByteSize());
}

TEST(DataTest, Bytes) {
  auto data = Data::Bytes(1);
  EXPECT_EQ(8, data.getBitSize());
  EXPECT_EQ(1, data.getByteSize());
}

TEST(DataTest, FromBytesVector) {
  std::vector<uint8_t> dataVec = { 1 };
  auto data = Data::fromBytesVector(dataVec);
  EXPECT_EQ(1, data.getByteSize());
  EXPECT_EQ(8, data.getBitSize());
  EXPECT_EQ(1, data.getByte(0));
  EXPECT_EQ(1, data.getBit(7));
  EXPECT_EQ(dataVec, data.toVector());
}

TEST(DataTest, FromBitsVector) {
  std::vector<uint8_t> dataVec = { 0, 0, 0, 0, 0, 1, 0, 1 };
  auto data = Data::fromBitsVector(dataVec);
  EXPECT_EQ(1, data.getByteSize());
  EXPECT_EQ(8, data.getBitSize());
  EXPECT_EQ(5, data.getByte(0));
}

TEST(DataTest, FromString) {
  std::string str = "test string";
  auto data = Data::fromString(str);
  EXPECT_EQ(str, data.toString());
  EXPECT_EQ(11, data.getByteSize());
  EXPECT_EQ(11 * 8, data.getBitSize());
}

TEST(DataTest, FromHexString) {
  std::string str = "5b5a57676a56676e";
  Data data = Data::fromHexString(str);
  EXPECT_EQ(str, data.toHexString());
  EXPECT_EQ(8, data.getByteSize());
  EXPECT_EQ(8 * 8, data.getBitSize());
}

TEST(DataTest, FromBinString) {
  std::string str = "0000 0101";
  Data data = Data::fromBinaryString(str);
  EXPECT_EQ(str, data.toBinString());
  EXPECT_EQ(1, data.getByteSize());
  EXPECT_EQ(8, data.getBitSize());
  EXPECT_EQ(5, data.getByte(0));
}

TEST(DataTest, SetBitByte) {
  auto data = Data::Bits(8);
  data.setBit(0, true);
  data.setBit(1, true);
  data.setBit(7, true);
  
  EXPECT_EQ(true, data.getBit(0));
  EXPECT_EQ(true, data.getBit(1));
  EXPECT_EQ(true, data.getBit(7));
  EXPECT_EQ(false, data.getBit(2));
  EXPECT_EQ(false, data.getBit(6));
  EXPECT_EQ(193, data.getByte(0));
  EXPECT_EQ("1100 0001", data.toBinString());

  data.setByte(0, 255);
  EXPECT_EQ(255, data.getByte(0));

  data.setBit(7, false);
  EXPECT_EQ(254, data.getByte(0));
}

TEST(DataTest, SliceBytes) {
  auto data = Data::Bits(24);
  data.setByte(0, 1);
  data.setByte(1, 2);
  data.setByte(2, 3);

  Data slice1 = data.sliceBytes(0, 1);
  Data slice2 = data.sliceBytes(1, 3);

  EXPECT_EQ(1, slice1.getByteSize());
  EXPECT_EQ(2, slice2.getByteSize());

  EXPECT_EQ(1, slice1.getByte(0));
  EXPECT_EQ(2, slice2.getByte(0));
  EXPECT_EQ(3, slice2.getByte(1));
}

TEST(DataTest, OperatorPlus) {
  auto data1 = Data::fromBinaryString("0000 0001");
  auto data2 = Data::fromBinaryString("0000 0010");
  auto data3 = data1 + data2;
  EXPECT_EQ(2, data3.getByteSize());
  EXPECT_EQ(16, data3.getBitSize());
  EXPECT_EQ("0000 0001 0000 0010", data3.toBinString());
}

TEST(DataTest, OperatorPlusEq) {
  auto data1 = Data::fromBinaryString("0000 0001");
  auto data2 = Data::fromBinaryString("0000 0010");
  data1 += data2;
  EXPECT_EQ(2, data1.getByteSize());
  EXPECT_EQ(16, data1.getBitSize());
  EXPECT_EQ("0000 0001 0000 0010", data1.toBinString());
}

TEST(DataTest, OperatorAnd) {
  auto data1 = Data::fromBinaryString("0101 0101");
  auto data2 = Data::fromBinaryString("0110 0110");
  auto data3 = data1 & data2;
  EXPECT_EQ("0100 0100", data3.toBinString());
  EXPECT_EQ(1, data3.getByteSize());
  EXPECT_EQ(8, data3.getBitSize());
}

TEST(DataTest, OperatorAndEq) {
  auto data1 = Data::fromBinaryString("0101 0101");
  auto data2 = Data::fromBinaryString("0110 0110");
  data1 &= data2;
  EXPECT_EQ("0100 0100", data1.toBinString());
  EXPECT_EQ(1, data1.getByteSize());
  EXPECT_EQ(8, data1.getBitSize());
}

TEST(DataTest, OperatorOr) {
  auto data1 = Data::fromBinaryString("0101 0101");
  auto data2 = Data::fromBinaryString("0110 0110");
  auto data3 = data1 | data2;
  EXPECT_EQ("0111 0111", data3.toBinString());
  EXPECT_EQ(1, data3.getByteSize());
  EXPECT_EQ(8, data3.getBitSize());
}

TEST(DataTest, OperatorOrEq) {
  auto data1 = Data::fromBinaryString("0101 0101");
  auto data2 = Data::fromBinaryString("0110 0110");
  data1 |= data2;
  EXPECT_EQ("0111 0111", data1.toBinString());
  EXPECT_EQ(1, data1.getByteSize());
  EXPECT_EQ(8, data1.getBitSize());
}

TEST(DataTest, OperatorXor) {
  auto data1 = Data::fromBinaryString("0101 0101");
  auto data2 = Data::fromBinaryString("0110 0110");
  auto data3 = data1 ^ data2;
  EXPECT_EQ("0011 0011", data3.toBinString());
  EXPECT_EQ(1, data3.getByteSize());
  EXPECT_EQ(8, data3.getBitSize());
}

TEST(DataTest, OperatorXorEq) {
  auto data1 = Data::fromBinaryString("0101 0101");
  auto data2 = Data::fromBinaryString("0110 0110");
  data1 ^= data2;
  EXPECT_EQ("0011 0011", data1.toBinString());
  EXPECT_EQ(1, data1.getByteSize());
  EXPECT_EQ(8, data1.getBitSize());
}

TEST(DataTest, OperatorNot) {
  auto data1 = Data::fromBinaryString("0101 0101");
  auto data2 = ~data1;
  EXPECT_EQ("1010 1010", data2.toBinString());
  EXPECT_EQ(1, data2.getByteSize());
  EXPECT_EQ(8, data2.getBitSize());
}

TEST(DataTest, Md5) {
  auto data = Data::fromString("password");
  auto hash = data.md5();
  EXPECT_EQ("5f4dcc3b5aa765d61d8327deb882cf99", hash.toHexString());
}

TEST(DataTest, Sha256) {
  auto data = Data::fromString("password");
  auto hash = data.sha256();
  EXPECT_EQ("5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8", hash.toHexString());
}

TEST(DataTest, Sha512) {
  auto data = Data::fromString("password");
  auto hash = data.sha512();
  EXPECT_EQ("b109f3bbbc244eb82441917ed06d618b9008dd09b3befd1b5e07394c706a8bb980b1d7785e5976ec049b46df5f1326af5a2ea6d103fd07c95385ffab0cacbc86", hash.toHexString());
}