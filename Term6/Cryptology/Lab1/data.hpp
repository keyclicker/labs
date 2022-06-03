#pragma once

#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>

class Data {
private:
  std::vector<uint8_t> data_;

public:
  Data() = default;
  Data(const Data &) = default;
  Data(Data &&) = default;
  Data &operator=(const Data &) = default;
  Data &operator=(Data &&) = default;

  explicit Data(size_t size) : data_(size) {}
  explicit Data(std::vector<uint8_t> data) : data_(std::move(data)) {}
  Data(const std::vector<uint8_t> &data, size_t size);

  static Data join(const std::vector<Data> &data);
  static Data from_hex(const std::string &hex);
  static Data from_string(const std::string &str);

  std::string to_hex() const;
  std::string to_string() const;

  Data shift_left(size_t shift);
  std::vector<Data> chop(size_t chunk_size) const;

  uint8_t operator[](size_t i) const;
  uint8_t &operator[](size_t i);
  [[nodiscard]] size_t size() const;

  Data operator^(const Data &rhs) const;
  Data operator+(const Data &rhs) const;

  Data slice(size_t start, size_t end) const;
  [[nodiscard]] std::pair<Data, Data> halve() const;

  Data permutate(const size_t perm_table[], size_t size) const;

  friend std::ostream &operator<<(std::ostream &os, const Data &data);
};