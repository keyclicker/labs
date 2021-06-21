#include <iostream>
#include "FibonacciHeap.hpp"

int main() {
  auto* heap = new FibonacciHeap<int>();
  int ar[10] = { 4, 2, 3, 6, 5, 1, 8, 7, 9};

  for(int i = 0; i < 9; i++){

    heap->insert(ar[i]);
    std::cout << "------------insert---------\n";
    heap->print();

  }

  heap->erase(5);
  std::cout << "------------delete-------------\n";
  heap->print();

  heap->decreaseKey(4, -1);
  std::cout << "------------decrease key-------------\n";
  heap->print();


  for(int i = 0; i < 8; i++) {
    heap->extractMin();
    std::cout << "------------extract min-------------\n";
    heap->print();
  }
}