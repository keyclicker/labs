#include <list>

struct Node {
  int value;
  Node* next;
};

Node *add(Node *first, Node *second) {
  Node *a = new Node();
  a->value = first->value + second->value;
  
  while (first || second) {
    a->next = new Node();
    if (first) {
      a->value += first->value;
      first = first->next;
    }
    if (second) {
      a->value += second->value;
      second = second->next;
    }
  }

  return a;
}