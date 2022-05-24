#pragma once

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <strstream>
#include <iomanip>

#include <openssl/sha.h>
#include <openssl/md5.h>

class Data {
  std::size_t size; //bitsize
  std::vector<uint8_t> data;
 
  public:
    Data(std::size_t size) : size(size), data(size / 8) {}
    
    Data(std::vector<uint8_t> data) : 
    size(data.size() * 8), data(std::move(data)) {}
    
    Data(const std::string &data) : 
    size(data.size() * 8), data(data.begin(), data.end()) {}

    static Data fromHexString(const std::string &hexString) {
      std::size_t size = hexString.size() / 2;
      std::vector<uint8_t> data(size);
      for (std::size_t i = 0; i < size; i++) {
        std::string byteString = hexString.substr(i * 2, 2);
        data[i] = (uint8_t)strtol(byteString.c_str(), nullptr, 16);
      }
      return Data(data);
    }

    std::size_t getSize() const {
      return size;
    }

    uint8_t getByte(std::size_t index) const {
      return data[index];
    }

    void setByte(std::size_t index, uint8_t value) {
      data[index] = value;
    }

    bool getBit(std::size_t index) const {
      return bool(data[index / 8] & (1 << (7 - index % 8)));
    }

    void setBit(std::size_t index, bool value) {
      std::size_t byteIndex = index / 8;
      std::size_t bitIndex = 7 - index % 8;

      if (value) {
        data[byteIndex] |= (1 << bitIndex);
      } else {
        data[byteIndex] &= ~(1 << bitIndex);
      }
    }

    Data sha256() {
      SHA256_CTX ctx;
      SHA256_Init(&ctx);
      SHA256_Update(&ctx, (uint8_t*) data.data(), data.size());
      std::vector<uint8_t> hash(32);
      SHA256_Final(hash.data(), &ctx);
      return Data(std::move(hash));
    }

    Data md5() {
      MD5_CTX ctx;
      MD5_Init(&ctx);
      MD5_Update(&ctx, (uint8_t*) data.data(), data.size());
      std::vector<uint8_t> hash(16);
      MD5_Final(hash.data(), &ctx);
      return Data(std::move(hash));
    }

    std::string toString() const {
      return std::string((char*) data.data(), data.size());
    }

    std::vector<uint8_t> &toVector() {
      return data;
    }

    std::string toHexString() const {
      std::strstream ss;
      for (uint8_t byte : data) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int) byte;
      }
      return ss.str();
    }

    std::string toBinString() {
      std::strstream ss;
      for (uint8_t byte : data) {
        for (int i = 7; i >= 0; i--) {
          ss << ((byte >> i) & 1);
        }
      }
      return ss.str();
    }

    Data sliceBytes(std::size_t start, std::size_t end) const {
      std::vector<uint8_t> slicedData(end - start);
      for (std::size_t i = start; i < end; i++) {
        slicedData[i - start] |= data[i];
      }
      return Data(std::move(slicedData));
    }

    Data operator^(const Data &other) const {
      if (size != other.size) {
        throw std::runtime_error("Data::operator^: size mismatch");
      }
      Data result(size);
      for (std::size_t i = 0; i < data.size(); i++) {
        result.setByte(i, data[i] ^ other.data[i]);
      }
      return result;
    }
};