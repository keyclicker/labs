#include <iostream>
#include "FibonacciHeap.hpp"
using namespace std;

int main() {
  auto* heap = new FibonacciHeap<int>();
  int ar[10] = { 4, 2, 3, 6, 5, 1, 8, 7, 9};

  for(int i = 0; i < 9; i++){
    heap->insert(ar[i]);
    cout << "insert(" << ar[i] << "):\n";
    heap->print();
    cout << endl;
  }

  heap->erase(5);
  cout << "erase(5):\n";
  heap->print();
  cout << endl;

  heap->decreaseKey(4, -1);
  cout << "decreaseKey(4, -1):\n";
  heap->print();
  cout << endl;


  for(int i = 0; i < 8; i++) {
    heap->extractMin();
    cout << "extractMin():\n";
    heap->print();
    cout << endl;
  }
}