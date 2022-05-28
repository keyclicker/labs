#include "Data.hpp"

#include <algorithm>
#include <sstream>

#include <openssl/sha.h>
#include <openssl/md5.h>

Data Data::Bytes(std::size_t size) {
  return Data(size * 8);
}

Data Data::Bits(std::size_t size) {
  return Data(size);
}

Data Data::fromBytesVector(std::vector<uint8_t> data) {
  return Data(std::move(data));
}

Data Data::fromBitsVector(const std::vector<uint8_t> &data) {
  Data res(data.size());
  for (std::size_t i = 0; i < data.size(); ++i) {
    res.setBit(i, data[i]);
  }
  return res;
}

Data Data::fromString(const std::string &str) {
  return Data(str);
}

Data Data::fromBinaryString(std::string binStr) {
  binStr.erase(remove(binStr.begin(), binStr.end(), ' '), binStr.end());
  Data res(binStr.size());
  for (std::size_t i = 0; i < binStr.size(); ++i) {
    res.setBit(i, binStr[i] == '1');
  }
  return res;
}

Data Data::fromHexString(const std::string &binStr) {
  std::size_t size = binStr.size() / 2;
  std::vector<uint8_t> data(size);
  for (std::size_t i = 0; i < size; i++) {
    std::string byteString = binStr.substr(i * 2, 2);
    data[i] = (uint8_t)strtol(byteString.c_str(), nullptr, 16);
  }
  return Data::fromBytesVector(data);
}

std::size_t Data::getBitSize() const {
  return bitSize;
}

std::size_t Data::getByteSize() const {
  return bitSize / 8;
}

void Data::resizeBytes(std::size_t size) {
  resizeBits(size * 8);
}

void Data::resizeBits(std::size_t size) {
  bitSize = size;
  data.resize(size / 8 + (size % 8 != 0));
}

uint8_t Data::getByte(std::size_t index) const {
  return data[index];
}

void Data::setByte(std::size_t index, uint8_t value) {
  data[index] = value;
}

bool Data::getBit(std::size_t index) const {
  return bool(data[index / 8] & (1 << (7 - index % 8)));
}

void Data::setBit(std::size_t index, bool value) {
  std::size_t byteIndex = index / 8;
  std::size_t bitIndex = 7 - index % 8;

  if (value) {
    data[byteIndex] |= (1 << bitIndex);
  } else {
    data[byteIndex] &= ~(1 << bitIndex);
  }
}

Data Data::sha256() const {
  SHA256_CTX ctx;
  SHA256_Init(&ctx);
  SHA256_Update(&ctx, (uint8_t*) data.data(), data.size());
  std::vector<uint8_t> hash(32);
  SHA256_Final(hash.data(), &ctx);
  return Data(std::move(hash));
}

Data Data::sha512() const {
  SHA512_CTX ctx;
  SHA512_Init(&ctx);
  SHA512_Update(&ctx, (uint8_t*) data.data(), data.size());
  std::vector<uint8_t> hash(64);
  SHA512_Final(hash.data(), &ctx);
  return Data(std::move(hash));
}

Data Data::md5() const {
  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, (uint8_t*) data.data(), data.size());
  std::vector<uint8_t> hash(16);
  MD5_Final(hash.data(), &ctx);
  return Data(std::move(hash));
}

std::string Data::toString() const {
  return std::string((char*) data.data(), data.size());
}

std::vector<uint8_t> Data::toVector() const {
  return data;
}

std::string Data::toHexString() const {
  std::stringstream ss;
  for (uint8_t byte : data) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int) byte;
  }
  return ss.str();
}

std::string Data::toBinString() const {
  std::stringstream ss;
  for (std::size_t i = 0; i < data.size(); ++i) {
    for (int8_t j = 7; j >= 0; j--) {
      if (j == 3) ss << " ";
      ss << bool((data[i] >> j) & 1);
    }
    if (i != data.size() - 1) ss << " ";
  }
  return ss.str();
}

Data Data::sliceBytes(std::size_t start, std::size_t end) const {
  std::vector<uint8_t> slicedData(end - start);
  for (std::size_t i = start; i < end; i++) {
    slicedData[i - start] |= data[i];
  }
  return Data(std::move(slicedData));
}


Data Data::operator+(const Data &rhs) const {
  Data result{};
  result.bitSize = bitSize + rhs.bitSize;
  result.data.reserve(data.size() + rhs.data.size());
  result.data.insert(result.data.end(), data.begin(), data.end());
  result.data.insert(result.data.end(), rhs.data.begin(), rhs.data.end());
  return result;
}

Data &Data::operator+=(const Data &rhs) {
  bitSize += rhs.bitSize;
  data.reserve(data.size() + rhs.data.size());
  data.insert(data.end(), rhs.data.begin(), rhs.data.end());
  return *this;
}

Data Data::operator^(const Data &rhs) const {
  Data result(bitSize);
  for (std::size_t i = 0; i < data.size(); i++) {
    result.setByte(i, data[i] ^ rhs.data[i]);
  }
  return result;
}

Data Data::operator&(const Data &rhs) const {
  Data result(bitSize);
  for (std::size_t i = 0; i < data.size(); i++) {
    result.setByte(i, data[i] & rhs.data[i]);
  }
  return result;
}

Data Data::operator|(const Data &rhs) const {
  Data result(bitSize);
  for (std::size_t i = 0; i < data.size(); i++) {
    result.setByte(i, data[i] | rhs.data[i]);
  }
  return result;
}

// Data Data::operator<<(std::size_t shift) const;
// Data Data::operator>>(std::size_t shift) const;

Data &Data::operator^=(const Data &rhs) {
  for (std::size_t i = 0; i < data.size(); i++) {
    data[i] ^= rhs.data[i];
  }
  return *this;
}

Data &Data::operator&=(const Data &rhs) {
  for (std::size_t i = 0; i < data.size(); i++) {
    data[i] &= rhs.data[i];
  }
  return *this;
}

Data &Data::operator|=(const Data &rhs) {
  for (std::size_t i = 0; i < data.size(); i++) {
    data[i] |= rhs.data[i];
  }
  return *this;
}

// Data &Data::operator<<=(std::size_t shift);
// Data &Data::operator>>=(std::size_t shift);

Data Data::operator~() const {
  Data result(bitSize);
  for (std::size_t i = 0; i < data.size(); i++) {
    result.setByte(i, ~data[i]);
  }
  return result;
}

