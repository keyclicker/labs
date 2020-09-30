#pragma once
#include <algorithm>
#include <istream>
#include <iomanip>
#include <vector>
#include <random>
#include <memory>
#include <list>

//Task 1
template<typename T>
class Tree {
public:
  std::shared_ptr<T> value;
  std::shared_ptr<std::vector<Tree>> children;

  explicit Tree(const T &val = T()) :
  value(new T(val)), children(new std::vector<Tree>()) {}

  //Task 2
  template<typename List>
  Tree getNode(const List &path) {
    Tree node = *this;
    for (auto a : path)
      node = (*node.children)[a];
    return node;
  }

  void addNode(const T &val) {
    children->push_back(Tree(val));
  }

  //Task 3
  template<typename List>
  void addNode(const List &path, const T &val) {
    Tree node = *this;
    for (auto a : path)
      node = (*node.children)[a];
    node.addNode(val);
  }

  //Task 15
  void removeValue(const T &val) {
    children->erase(std::remove_if(children->begin(), children->end(),
          [val] (Tree node) { return *(node.value) == val; }), children->end());
    for (auto &a : *children)
      a.removeValue(val);
  }

  //Task 8
  void print() const {
    static std::list<std::string> tree;

    if (tree.empty()) std::cout << "Root: ";
    else std::cout << "  ";

    std::cout << "Val:" << std::setw(3) << *value
  //  << "  sub:" << std::setw(2) << children->size()
    << std::endl;

    if (!children->empty()) {
      for (auto a = children->begin(); a != --children->end(); ++a) {
        for (auto &a : tree)
          std::cout << a;
        tree.emplace_back("│     ");

        std::cout << "├────" << std::setw(2) << a - children->begin() << ':';
        a->print();
        tree.pop_back();
      }

      for (auto &a : tree)
        std::cout << a;
      tree.emplace_back("      ");

      std::cout << "└────" << std::setw(2) << children->size() - 1 << ':';
      children->back().print();
      tree.pop_back();
    }
  }

  //Task 11
  void printAllPaths() const {
    static std::list<T> path;
    path.push_back(*value);

    if (children->empty()) {
      for (auto a : path)
        std::cout << " ->"<< std::setw(4) << a;
      std::cout << std::endl;
    }
    else
      for (auto a : *children)
        a.printAllPaths();

    path.pop_back();
  }

  void genRandom(size_t size) {
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int> randval(0, 100), randsize(size/4, size/2);

    *value = T(randval(re));

    auto rs = randsize(re);
    children->reserve(rs);

    for (int i = 0; i < rs; ++i) {
      children->push_back(Tree());
      children->back().genRandom(size - rs);
    }
  }
};