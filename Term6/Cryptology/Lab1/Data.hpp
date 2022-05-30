#pragma once

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <strstream>
#include <iomanip>

class Data {
  std::size_t bitSize; //bitsize
  std::vector<uint8_t> data;

  Data(): bitSize(0), data() {}

  explicit Data(std::size_t bitSize):
  bitSize(bitSize), 
  data(bitSize / 8 + (bitSize % 8 != 0)) {};

  explicit Data(std::vector<uint8_t> data):
  bitSize(data.size() * 8),
  data(std::move(data)) {};

  explicit Data(const std::string &data) :
  bitSize(data.size() * 8), 
  data(data.begin(), data.end()) {}

public:
  static Data Bytes(std::size_t size);
  static Data Bits(std::size_t size);

  static Data fromBytesVector(std::vector<uint8_t> data);
  static Data fromBitsVector(const std::vector<uint8_t> &data);

  static Data fromHexString(const std::string &binStr);
  static Data fromString(const std::string &str);
  static Data fromBinaryString(std::string hexStr);

  template<typename T>
  static Data fromObject(const T &obj);

  [[nodiscard]] std::size_t getBitSize() const;
  [[nodiscard]] std::size_t getByteSize() const;

  void resizeBytes(std::size_t size);
  void resizeBits(std::size_t size);

  [[nodiscard]] uint8_t getByte(std::size_t index) const;
  void setByte(std::size_t index, uint8_t value);
  [[nodiscard]] bool getBit(std::size_t index) const;
  void setBit(std::size_t index, bool value);

  // << left shift
  Data rotatedBits(int64_t count) const;

  [[nodiscard]] Data sliceBytes(std::size_t start, std::size_t end) const;
  [[nodiscard]] Data sliceBits(std::size_t start, std::size_t end) const;

  Data operator+(const Data &rhs) const;
  Data &operator+=(const Data &rhs);

  Data operator^(const Data &rhs) const;
  Data operator&(const Data &rhs) const;
  Data operator|(const Data &rhs) const;

  // Data operator<<(std::size_t shift) const;
  // Data operator>>(std::size_t shift) const;

  Data &operator^=(const Data &rhs);
  Data &operator&=(const Data &rhs);
  Data &operator|=(const Data &rhs);

  // Data &operator<<=(std::size_t shift);
  // Data &operator>>=(std::size_t shift);

  Data operator~() const;

  [[nodiscard]] Data md5() const;
  [[nodiscard]] Data sha256() const;
  [[nodiscard]] Data sha512() const;


  [[nodiscard]] std::vector<uint8_t> toVector() const;
  [[nodiscard]] std::string toString() const;
  [[nodiscard]] std::string toHexString() const;
  [[nodiscard]] std::string toBinString() const;

  template<typename T> 
  [[nodiscard]] T toObject() const;
};


template<typename T>
Data Data::fromObject(const T &obj) {
  Data res(sizeof(obj) * 8);
  for (std::size_t i = 0; i < sizeof(obj); ++i) {
    res.setByte(i, ((uint8_t*)&obj)[i]);
  }
}

template<typename T> 
T Data::toObject() const {
  T res;
  for (std::size_t i = 0; i < sizeof(res); ++i) {
    ((uint8_t*)&res)[i] = getByte(i);
  }
  return res;
};
