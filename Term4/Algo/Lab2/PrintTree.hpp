#pragma once

#include <list>
#include <string>
#include <iostream>
#include <iomanip>

template <typename N>
void printTree(N *node) {
  static std::list<std::string> tree;

  if (tree.empty()) std::cout << "Root: ";
  else std::cout << "  ";

  std::cout << "Key: " << std::setw(3) << node->pair.first
            << "  Val: " << node->pair.second
            << std::endl;

  if (node->left) {
    for (auto &a: tree)
      std::cout << a;

    if (node->right) {
      tree.emplace_back("\xB3     ");
      std::cout << "\xC3\xC4\xC4\xC4\xC4" << std::setw(2) << " L:";
    }
    else {
      tree.emplace_back("      ");
      std::cout << "\xC0\xC4\xC4\xC4\xC4" << std::setw(2) << " L:";
    }

    printTree(node->left);
    tree.pop_back();
  }

  if (node->right) {
    for (auto &a: tree)
      std::cout << a;

    tree.emplace_back("      ");

    std::cout << "\xC0\xC4\xC4\xC4\xC4" << std::setw(2) << " R:";
    printTree(node->right);
    tree.pop_back();
  }
}