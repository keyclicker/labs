#include "FileSystem.hpp"
#include "BinaryTree.hpp"
#include "Tree.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <memory>
#include <map>
using namespace std;

void maketree (); // Task 1
void gentree();
void get(); // Task 2
void add(); // Task 3
void tree(); // Task 8
void paths(); // Task 11
void remove(); // Task 15


void makebintree(); // Task 18
void treebin();
void addbin(); // Task 18
void inorder(); // Task 18
void preorder(); // Task 21

// Task 26:
void makedir();
void treefo();
void size();
void mintime();
void maxtime();

void help();
void demo();

map<string, shared_ptr<Tree<int>>> trees;
map<string, shared_ptr<BinaryTree<int>>> bintrees;
map<string, shared_ptr<FileObject>> fileobjects;

int main() {
  cout << "Type \"help\" to get help" << endl;

  string cmd;

  while (cmd != "exit") {
    cin >> cmd;

    if (cmd ==  "mktree") maketree ();
    else if (cmd == "gentree") gentree();
    else if (cmd == "get") get();
    else if (cmd == "add") add();
    else if (cmd == "tree") tree();
    else if (cmd == "paths") paths();
    else if (cmd == "remove") remove();
    else if (cmd == "mkbintree") makebintree();
    else if (cmd == "treebin") treebin();
    else if (cmd == "addbin") addbin();
    else if (cmd == "inorder") inorder();
    else if (cmd == "preorder") preorder();
    else if (cmd == "mkdir") makedir();
    else if (cmd == "treefo") treefo();
    else if (cmd == "size") size();
    else if (cmd == "mintime") mintime();
    else if (cmd == "maxtime") maxtime();
    else if (cmd == "help") help();
    else if (cmd == "demo") demo();
  }
}

void help() {
  constexpr int w = 30;

  cout << setw(w) << left <<
       "mktree <name>" << "Make tree" << endl;
  cout << setw(w) << left <<
       "gentree <name>" << "Generate random tree" << endl;
  cout << setw(w) << left <<
       "get <name> <path>" << "Get subtree by <path>" << endl;
  cout << setw(w) << left <<
       "add <name> <value> <path>" << "Add value to path" << endl;
  cout << setw(w) << left <<
       "tree <name>" << "Tree print (class Tree)" << endl;
  cout << setw(w) << left <<
       "paths <name>" << "Print all paths of tree" << endl;
  cout << setw(w) << left <<
       "remove <name> <value>" << "Remove all values of tree" << endl;
  cout << setw(w) << left <<
       "mkbintree <name>" << "Generate random binary tree" << endl;
  cout << setw(w) << left <<
       "treebin <name>" << "Tree print (class BinaryTree)" << endl;
  cout << setw(w) << left <<
       "addbin <name> <value>" << "Add value to binary tree (and sort)" << endl;
  cout << setw(w) << left <<
       "inorder <name>" << "Inorder print of binary tree" << endl;
  cout << setw(w) << left <<
       "preorder <name>" << "Preorder print of binary tree" << endl;
  cout << setw(w) << left <<
       "mkdir <name>" << "Generate random dir" << endl;
  cout << setw(w) << left <<
       "treefo <name>" << "Tree print (class FileObject)" << endl;
  cout << setw(w) << left <<
       "size <name>" << "Print size of root folder" << endl;
  cout << setw(w) << left <<
       "mintime <name>" << "Print min time of changes" << endl;
  cout << setw(w) << left <<
       "maxtime <name>" << "Print max time of changes (last changes)" << endl;
}

void maketree() {
  string name;
  cin >> name;
  trees[name] = std::make_shared<Tree<int>>();
}

void gentree() {
  string name;
  cin >> name;
  trees[name] = std::make_shared<Tree<int>>();
  trees[name]->genRandom(10);
}

void get() {
  string name, vals;
  cin >> name;

  getline(cin, vals);
  stringstream st(vals);

  list<int> path;
  while (!st.eof()) {
    int val;
    st >> val;
    path.push_back(val);
  }
  trees[name]->getNode(path).print();
}

void add() {
  int value;
  string name, vals;
  cin >> name >> value;

  getline(cin, vals);
  stringstream st(vals);

  list<int> path;
  while (!st.eof()) {
    int val;
    st >> val;
    path.push_back(val);
  }
  trees[name]->addNode(path, value);
}

void tree() {
  string name;
  cin >> name;
  trees[name]->print();
}

void paths() {
  string name;
  cin >> name;
  trees[name]->printAllPaths();
}

void remove() {
  string name;
  int value;
  cin >> name >> value;
  trees[name]->removeValue(value);
}

void makebintree() {
  string name;
  cin >> name;
  bintrees[name] = std::make_shared<BinaryTree<int>>();
  bintrees[name]->genRandom(10);
}

void addbin() {
  string name;
  int value;
  cin >> name >> value;
  bintrees[name]->insertValue(value);
}

void inorder() {
  string name;
  cin >> name;
  bintrees[name]->sortedPrint();
}

void preorder() {
  string name;
  cin >> name;
  bintrees[name]->preorderPrint();
}

void makedir() {
  string name;
  cin >> name;
  fileobjects[name] = std::make_shared<FileObject>();
  fileobjects[name]->genRandom(10);
}

void size() {
  string name;
  cin >> name;
  cout << fileobjects[name]->getSize() << " bytes" << endl;
}

void mintime() {
  string name;
  cin >> name;
  cout << fileobjects[name]->getMinTime() << endl;
}

void maxtime() {
  string name;
  cin >> name;
  cout << fileobjects[name]->getMaxTime() << endl;
}

void treebin() {
  string name;
  cin >> name;
  bintrees[name]->print();
}

void treefo() {
  string name;
  cin >> name;
  fileobjects[name]->print();
}

void demo() {
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
