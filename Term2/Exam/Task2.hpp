#pragma once

#include <algorithm>

struct Node {
  int value;
  Node *left, *right;
};

Node *minN, *maxN;

void minNode(Node *root) {
  if (minN->value > root->value)
    minN = root;
  if (root->right)
    minNode(root->right);
  if (root->left)
    minNode(root->left);
}

void maxNode(Node *root) {
  if (maxN->value < root->value)
    maxN = root;
  if (root->right)
    maxNode(root->right);
  if (root->left)
    maxNode(root->left);
}

void swapMinMax(Node *root) {
  minN = root;
  minNode(root);
  maxN = root;
  maxNode(root);

  std::swap(minN->value, maxN->value);
}