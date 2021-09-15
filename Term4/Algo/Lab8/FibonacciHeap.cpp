#pragma once
#include "FibonacciHeap.hpp"

#include <vector>
#include <iostream>

template<typename T>
void FibonacciHeap<T>::addToRootsList(FibonacciHeap::Node *toAdd, bool allLevel) {

  if (allLevel) {
    Node *leftHeadBrother = head->leftBrother;
    toAdd->leftBrother->rightBrother = head;
    head->leftBrother = toAdd->leftBrother;
    toAdd->leftBrother = leftHeadBrother;
    leftHeadBrother->rightBrother = toAdd;
  } else {
    toAdd->leftBrother = head->leftBrother;
    toAdd->rightBrother = head;
    toAdd->leftBrother->rightBrother = toAdd;
    head->leftBrother = toAdd;
  }

  if (head->value > toAdd->value) {
    head = toAdd;
  }
}

template<typename T>
void FibonacciHeap<T>::eraseFromRootsList(FibonacciHeap::Node *toDelete) {

  toDelete->leftBrother->rightBrother = toDelete->rightBrother;
  toDelete->rightBrother->leftBrother = toDelete->leftBrother;

  if (toDelete == head) {
    head = toDelete->leftBrother;
  }
}

template<typename T>
typename FibonacciHeap<T>::Node *FibonacciHeap<T>::heapUnion(FibonacciHeap::Node *toUnite1, FibonacciHeap::Node *toUnite2) {

  if (toUnite1 == nullptr) {
    return toUnite2;
  }
  if (toUnite2 == nullptr) {
    return toUnite1;
  }

  toUnite1->rightBrother->leftBrother = toUnite2->leftBrother;
  toUnite2->leftBrother->rightBrother = toUnite1->rightBrother;
  toUnite1->rightBrother = toUnite2;
  toUnite2->leftBrother = toUnite1;

  if (toUnite1->value > toUnite2->value) {
    return toUnite2;
  }

  return toUnite1;
}

template<typename T>
void FibonacciHeap<T>::consolidate() {
  std::vector<Node *> degrees;
  degrees.resize(size, nullptr);

  Node *temp = head;
  Node *toLink;
  int d;
  while (!temp->visited && temp->leftBrother != temp) {
    d = temp->degree;
    temp->visited = true;
    while (degrees[d] != nullptr) {
      toLink = degrees[d];
      if (temp->value <= toLink->value) {
        link(toLink, temp);
      } else {
        link(temp, toLink);
        temp = toLink;
      }
      degrees[d] = nullptr;
      d++;
    }
    degrees[d] = temp;
    temp = temp->rightBrother;
  }

  temp = head;

  do {
    if (temp->value < head->value) {
      head = temp;
    }
    temp = temp->rightBrother;
  } while (temp != head);

}

template<typename T>
void FibonacciHeap<T>::link(FibonacciHeap::Node *greaterRoot, FibonacciHeap::Node *lesserRoot) {
  eraseFromRootsList(greaterRoot);

  if (lesserRoot->child != nullptr) {
    greaterRoot->leftBrother = lesserRoot->child->leftBrother;
    greaterRoot->rightBrother = lesserRoot->child;

    greaterRoot->leftBrother->rightBrother = greaterRoot;
    greaterRoot->rightBrother->leftBrother = greaterRoot;
  } else {
    greaterRoot->leftBrother = greaterRoot;
    greaterRoot->rightBrother = greaterRoot;
  }

  lesserRoot->child = greaterRoot;
  greaterRoot->parent = lesserRoot;
  lesserRoot->degree++;
  greaterRoot->mark = false;

  if (greaterRoot == head) {
    head = lesserRoot;
  }
}

template<typename T>
typename FibonacciHeap<T>::Node *FibonacciHeap<T>::findNodeByValue(FibonacciHeap::Node *toFind, T value) {
  if (toFind == nullptr) {
    return nullptr;
  }

  if (toFind->value == value) {
    return toFind;
  }

  Node *res;
  if (value >= toFind->value) {
    res = findNodeByValue(toFind->child, value);
    if (res != nullptr)
      return res;
  }
  if (((toFind->parent && toFind->leftBrother != toFind->parent->child) ||
       (!toFind->parent && toFind->leftBrother != head))) {
    res = findNodeByValue(toFind->leftBrother, value);
    if (res != nullptr) {
      return res;
    }
  }

  return nullptr;
}

template<typename T>
void FibonacciHeap<T>::cut(FibonacciHeap::Node *toCut) {
  if (toCut->leftBrother == toCut) {
    toCut->parent->child = nullptr;
  } else {
    toCut->leftBrother->rightBrother = toCut->rightBrother;
    toCut->rightBrother->leftBrother = toCut->leftBrother;
    if (toCut == toCut->parent->child) {
      toCut->parent->child = toCut->rightBrother;
    }
  }

  addToRootsList(toCut, false);
  toCut->parent = nullptr;
  toCut->mark = false;
}

template<typename T>
void FibonacciHeap<T>::cascadingCut(FibonacciHeap::Node *toCut) {
  if (toCut->parent != nullptr) {
    if (!toCut->mark) {
      toCut->mark = true;
    } else {
      cut(toCut);
      cascadingCut(toCut->parent);
    }
  }
}

template<typename T>
void FibonacciHeap<T>::print(FibonacciHeap::Node *node, int degree) {
  if (node == nullptr) {
    return;
  }

  for (int i = 0; i < degree; i++) {
    std::cout << "\t";
  }
  if (node == head) {
    std::cout << "head ";
  }
  std::cout << node->value << " | leftBrother " << node->leftBrother->value
            << " | rightBrother " << node->rightBrother->value
            << " | degree " << node->degree;
  if (node->parent != nullptr) {
    std::cout << "\tparent\t" << node->parent->value;
  }
  std::cout << "\n";

  print(node->child, degree + 1);
  if ((node->parent && node->leftBrother != node->parent->child) ||
      (!node->parent && node->leftBrother != head)) {
    print(node->leftBrother, degree);
  }

}

template<typename T>
void FibonacciHeap<T>::insert(T t) {
  Node *toInsert = new Node(t);
  if (head == nullptr) {
    head = toInsert;
  } else {
    addToRootsList(toInsert, true);
  }

  size++;
}

template<typename T>
T FibonacciHeap<T>::min() {
  return head->value;
}

template<typename T>
T FibonacciHeap<T>::extractMin() {
  Node *toDelete = head;
  Node *temp = toDelete->child;

  if (temp != nullptr) {
    addToRootsList(temp, true);
    temp = head;
    do {
      temp->parent = nullptr;
      temp->visited = false;
      temp = temp->rightBrother;
    } while (temp != head);

  }


  eraseFromRootsList(toDelete);
  if (toDelete == toDelete->rightBrother) {
    head = nullptr;
  } else {
    consolidate();
  }

  size--;
  return toDelete->value;
}

template<typename T>
void FibonacciHeap<T>::decreaseKey(T toDecrease, T decreased) {
  if (toDecrease <= decreased) {
    return;
  }

  Node *toFind = findNodeByValue(head, toDecrease);

  toFind->value = decreased;
  Node *parent = toFind->parent;
  if (parent != nullptr && toFind->value < toFind->parent->value) {
    cut(toFind);
    cascadingCut(parent);
  }

  if (toFind->value < head->value) {
    head = toFind;
  }
}

template<typename T>
void FibonacciHeap<T>::erase(T value) {
  decreaseKey(value, INT32_MIN);
  extractMin();
}

template<typename T>
void FibonacciHeap<T>::print() {
  print(head, 0);
}

template<typename T>
typename FibonacciHeap<T>::Node *FibonacciHeap<T>::getRoot() {
  return head;
}


