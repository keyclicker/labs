#pragma once
#include <algorithm>
#include <istream>
#include <iomanip>
#include <vector>
#include <random>
#include <memory>
#include <list>

//Task 18.1
template<typename T>
struct BinaryTree {
public:
  std::shared_ptr<T> value;
  std::shared_ptr<BinaryTree> left, right;

  explicit BinaryTree() : value(nullptr), left(nullptr), right(nullptr) {}
  explicit BinaryTree(const T &val) :
          value(new T(val)), left(nullptr), right(nullptr) {}

  //Task 18.2
  void insertValue(const T &val) {
    if (value == nullptr)
      value = std::shared_ptr<T>(new T(val));
    else {
      if (val <= *value) {
        if (!left) left = std::shared_ptr<BinaryTree>(new BinaryTree());
        left->insertValue(val);
      }
      else {
        if (!right) right = std::shared_ptr<BinaryTree>(new BinaryTree());
        right->insertValue(val);
      }
    }
  }

  void sortedPrint() const {
    static uint32_t depth = 0;
    depth++;

    if (left)
      left->sortedPrint();
    if (value)
      std::cout << *value << ' ';
    if (right)
      right->sortedPrint();

    depth--;
    if (!depth) std::cout << std::endl;
  }

  //Task 21
  void preorderPrint() const {
    static uint32_t depth = 0;
    depth++;

    if (value)
      std::cout << *value << ' ';
    if (left)
      left->preorderPrint();
    if (right)
      right->preorderPrint();

    depth--;
    if (!depth) std::cout << std::endl;
  }


  void print() const {
    // i've got some encoding problem with
    // '│' sign when i using char instead  string
    static std::list<std::string> tree;

    if (tree.empty()) std::cout << "Root: ";
    else std::cout << "  ";

    std::cout << "Val:" << std::setw(3) << *value << std::endl;


    if (left) {
      for (auto &a : tree)
        std::cout << a;
      tree.insert(tree.end(), {right ? "│" : " ", " ", " ", " ", " ", " "});

      std::cout << (right ? "├────" : "└────") << std::setw(2) << "<" << ':';
      left->print();

      for (int i = 0; i < 6; ++i)
        tree.pop_back();
    }

    if (right) {
      for (auto &a : tree)
        std::cout << a;
      tree.insert(tree.end(), {" ", " ", " ", " ", " ", " "});

      std::cout << "└────" << std::setw(2) << ">" << ':';
      right->print();

      for (int i = 0; i < 6; ++i)
        tree.pop_back();
    }
  }
};