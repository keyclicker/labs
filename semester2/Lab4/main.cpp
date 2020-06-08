#include <iostream>
#include <list>
#include "Tree.hpp"
#include "BinaryTree.hpp"

int main()
{
  Tree<int> tree;

  tree.genRandom(5);

  tree.printAllPaths();
  tree.print();

  tree.addNode(std::list<int>({0}), 228);
  tree.addNode(std::list<int>({0, 0}), 322);

  tree.print();

  tree.removeValue(228);
  tree.removeValue(322);

  tree.print();


  std::random_device rd;
  std::default_random_engine re(rd());
  std::uniform_int_distribution<int> randval(0, 100);

  BinaryTree<int> bt;
  for (int i = 0; i < 10; ++i) {
    bt.insertValue(randval(re));
  }

 // bt.print();

  bt.sortedPrint();
  bt.preorderPrint();

  bt.print();


}
