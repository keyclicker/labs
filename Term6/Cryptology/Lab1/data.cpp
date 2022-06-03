#include "data.hpp"

Data::Data(const std::vector<uint8_t> &data, size_t size) : data_(size) {
  if (data.size() <= size)
    for (size_t i = 0; i < data.size(); i++)
      data_[i] = data[i];
  else
    for (size_t i = 0; i < size; i++)
      data_[i + data.size() - size] = data[i];
}

Data Data::join(const std::vector<Data> &data) {
  size_t size = 0;
  for (const auto &d : data)
    size += d.size();
  Data res(size);
  size_t i = 0;
  for (const auto &d : data) {
    for (size_t j = 0; j < d.size(); j++)
      res[i++] = d[j];
  }
  return res;
}

Data Data::from_hex(const std::string &hex) {
  std::size_t size = hex.size() * 4;
  Data data(size);

  std::stringstream ss;
  int bits = 0;
  for (uint i = 0; i < size; ++i) {
    ss << hex[i];
    ss >> std::hex >> bits;
    data.data_[i * 4 + 3] = bits & 1;
    data.data_[i * 4 + 2] = bits >> 1 & 1;
    data.data_[i * 4 + 1] = bits >> 2 & 1;
    data.data_[i * 4] = bits >> 3 & 1;
    ss.clear();
  }
  return data;
}

Data Data::from_string(const std::string &str) {
  Data data(str.size() * 8);
  for (size_t i = 0; i < str.size(); i++)
    for (size_t j = 0; j < 8; j++)
      data[i * 8 + j] = str[i] >> j & 1;
  return data;
}

std::string Data::to_hex() const {
  std::stringstream ss;
  for (uint i = 0; i < data_.size(); i += 4) {
    uint8_t bits = 0;
    bits |= data_[i] << 3;
    bits |= data_[i + 1] << 2;
    bits |= data_[i + 2] << 1;
    bits |= data_[i + 3];
    ss << std::hex << (int)bits;
  }
  return ss.str();
}

std::string Data::to_string() const {
  std::stringstream ss;
  for (uint i = 0; i < data_.size(); i += 8) {
    uint8_t bits = 0;
    for (uint j = 0; j < 8; j++)
      bits |= data_[i + j] << j;
    ss << (char)bits;
  }
  return ss.str();
}

Data Data::shift_left(size_t shift) {
  Data shifted(data_.size());
  for (size_t i = 0; i < data_.size(); i++) {
    shifted[i] = data_[(i + shift) % data_.size()];
  }
  return shifted;
}

std::vector<Data> Data::chop(size_t chunk_size) const {
  std::vector<Data> chunks;
  for (size_t i = 0; i < data_.size(); i += chunk_size) {
    chunks.emplace_back(std::vector(
        data_.begin() + i, data_.begin() + i + chunk_size));
  }
  return chunks;
}

uint8_t Data::operator[](size_t i) const {
  return data_[i];
}

uint8_t &Data::operator[](size_t i) {
  return data_[i];
}

size_t Data::size() const {
  return data_.size();
}

Data Data::operator^(const Data &rhs) const {
  Data result(size());
  for (size_t i = 0; i < size(); ++i) {
    result[i] = data_[i] ^ rhs[i];
  }
  return result;
}

Data Data::operator+(const Data &rhs) const {
  Data result(size() + rhs.size());
  for (size_t i = 0; i < size(); ++i) {
    result[i] = data_[i];
  }
  for (size_t i = 0; i < rhs.size(); ++i) {
    result[i + size()] = rhs[i];
  }
  return result;
}

Data Data::slice(size_t start, size_t end) const {
  Data result(end - start);
  for (size_t i = start; i < end; ++i) {
    result[i - start] = data_[i];
  }
  return result;
}

std::pair<Data, Data> Data::halve() const {
  auto first = slice(0, size() / 2);
  auto second = slice(size() / 2, size());
  return std::make_pair(first, second);
}

Data Data::permutate(const size_t *perm_table, size_t size) const {
  Data result(size);
  for (size_t i = 0; i < size; ++i) {
    result[i] = data_[perm_table[i] - 1];
  }
  return result;
}

std::ostream &operator<<(std::ostream &os, const Data &data) {
  os << data.to_hex();
  return os;
}
