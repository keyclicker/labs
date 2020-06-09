#include <iostream>
#include <list>
using namespace std;

#include "Tree.hpp"
#include "BinaryTree.hpp"
#include "FileSystem.hpp"

int main()
{
  cout << "Generating random tree" << endl;
  Tree<int> tree;
  tree.genRandom(5);
  cout << endl;

  cout << "Printing all pathes in tree (Task 11):" << endl;
  tree.printAllPaths();
  cout << endl;

  cout << "Printing tree (Task 8?):" << endl;
  tree.print();
  cout << endl;

  cout << "Adding node 228 by path {0} and 322 by {0, 0} (Task 3):" << endl;
  tree.addNode(std::list<int>({0}), 228);
  tree.addNode(std::list<int>({0, 0}), 322);

  tree.print();
  cout << endl;

  cout << "Printing subtree gotten by path {0, 0} (Task 2):" << endl;
  tree.getNode(std::list<int>({0, 0})).print();
  cout << endl;

  cout << "Removing all values є {228, 322} (Task 15):" << endl;
  tree.removeValue(228);
  tree.removeValue(322);

  tree.print();
  cout << endl;


  std::random_device rd;
  std::default_random_engine re(rd());
  std::uniform_int_distribution<int> randval(0, 100);

  BinaryTree<int> bt;
  for (int i = 0; i < 10; ++i) {
    bt.insertValue(randval(re));
  }

  cout << "Creating binary tree, and adding of "
          "10 automatically sorted random values (Task 18):" << endl;
  bt.print();
  cout << endl;

  cout << "Inorder traversal:" << endl;
  bt.sortedPrint();
  cout << endl;

  cout << "Preorder traversal presentation (task 21):" << endl;
  bt.preorderPrint();
  cout << endl;

  cout << "Generating random file system tree (Task 26):\n" << endl;

  FileObject fs;
  fs.genRandom(10);
  fs.print();
  cout << endl;

  cout << "Max time: " << fs.getMaxTime() << endl;
  cout << "Min time: " << fs.getMinTime() << endl;

  cout << "\nFilter: no empty folders\n" << endl;

  fs.getIf([](const FileObject &fo) {
    return !(fo.getType() == FileObject
    ::Type::Directory && fo.getDir().empty());
  }).print();

  cout << "\nFilter: Modified before 22.05.2017, no empty folders\n" << endl;

  fs.getIf([](const FileObject &fo) {
    return !(fo.getType() == FileObject
    ::Type::Directory && fo.getDir().empty()) &&
    ((fo.getType() == FileObject ::Type::File &&
    fo.getMaxTime() < Time(22,05,2017)) ||
    fo.getType() == FileObject::Type::Directory);
  }).print();
}
