#pragma once

struct Node {
  int value;
  Node *left, *right;
};

void node_count(Node *root) {
  static int counter = 0;
  counter++;
  if (root.left) node_count(root->left);
  if (root.right) node_count(root->right);
}