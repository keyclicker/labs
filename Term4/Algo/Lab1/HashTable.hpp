#pragma once

#include <vector>


class HashTable {
private:
  using Pair = std::pair<std::string, std::string>;
  using Table = std::vector<Pair>;

  struct Item {
    int code;
    std::string key;
    std::string value;
  };

  struct Params {
    int a;
    int b;
  };
  
  static constexpr int prime = 101;
  static constexpr int pA = 3;
  static constexpr int pB = 42;
  
  std::vector<std::pair<std::vector<Item>, Params>> data;

  int h(const int &key) const {
    return ((pA * key + pB) % prime) % data.size();
  }

  void auxiliaryHash(std::pair<std::vector<Item>, Params> &cell) {
    std::vector<int> positions(cell.first.size(), 0);
    std::vector<Item> updatedCell(cell.first.size() * cell.first.size());

    for (int a = 0; a < prime; ++a) {
      for (int b = 0; b < prime - 1; ++b) {
        for (int i = 0; i < positions.size(); ++i) {
          positions[i] = hParam(cell.first[i].code, a, b, updatedCell.size());
        }
        if (collisionCheck(positions)) {
          cell.second.a = a;
          cell.second.b = b;

          for (int i = 0; i < positions.size(); ++i) {
            updatedCell[positions[i]] = cell.first[i];
          }
          cell.first = updatedCell;
          return;
        }
      }
    }
  }

  static int hParam(const int &key, int &a, int &b, const int &size) {
    return ((a * key + b) % prime) % size;
  }

  static bool collisionCheck(const std::vector<int> &positions) {
    std::vector<bool> array(prime, false);
    for (auto &i: positions) {
      if (array[i])
        return false;
      array[i] = true;
    }
    return true;
  }

public:
  explicit HashTable(const Table &input){
    data.resize(input.size());
    int position;

    for (auto &i: data) {
      i = std::pair(std::vector<Item>{}, Params());
    }

    for (auto &i: input) {
      int code = codeKey(i.first);
      position = h(code);

      Item item = {
          .code = code,
          .key = i.first,
          .value = i.second
      };

      data[position].first.emplace_back(item);
    }

    for (auto &i: data) {
      if (i.first.size() > 1) {
        auxiliaryHash(i);
      }
    }
  }

  static int codeKey(const std::string &key) {
    int code = 0;
    int powCounter = pA;
    for (int i = 0; i < key.size(); i++) {
      code = (code + (int(key[i]) * powCounter)) % prime;
      powCounter = (powCounter * pA) % prime;
    }
    return code % prime;
  }

  std::string operator[](const std::string &key) {
    return this->get(key).value;
  }

  Item get(const std::string &key) {
    int code = codeKey(key);
    std::pair<std::vector<Item>, Params> &cell = data[h(code)];
    return cell.first[hParam(code, cell.second.a, cell.second.b, cell.first.size())];
  }

  friend ostream& operator<<(ostream& os, const HashTable& ht) {
    for(auto &i: ht.data){
      os << i.first.size() << " " << i.second.a << " " << i.second.b << " | ";
      for(auto &j : i.first){
        os << "{" << j.code << ", " << j.key << ", " << j.value << "} ";
      }
      os << std::endl;
    }
    return os;
  }
};
