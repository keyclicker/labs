#pragma once

#include <cmath>
#include "SplayTree.hpp"


template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree(Node *root)
    : m_Root(root), m_Size(root ? 1 : 0) {}

template<typename Key, typename Value>
SplayTree<Key, Value>::~SplayTree() {
  clear();
}

template<typename Key, typename Value>
const Value &SplayTree<Key, Value>::search(const Key &key) const {
  Node *node = m_Root;

  while (node && key != node->pair.first)
    node = node->pair.first > key ? node->left : node->right;

  return node->pair.second;
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::clear() {
  delete m_Root;
  m_Root = nullptr;
}

template<typename Key, typename Value>
Value &SplayTree<Key, Value>::insert(const Key &key, const Value &value) {
  ++m_Size;

  if (!m_Root)
    return (m_Root = new Node(key, value))->pair.second;

  Node *node = m_Root;
  Node *parent = nullptr;

  while (node) {
    if (node->pair.first == key) {
      --m_Size;
      splay(node);
      return node->pair.second;
    }

    parent = node;
    node = node->pair.first > key ? node->left : node->right;
  }

  node = new Node(key, value, parent);

  if (parent->pair.first > key)
    parent->left = node;
  else
    parent->right = node;

  splay(node);

  return node->pair.second;
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::del(const Key &key) {
  Node *node = getNode(key);

  if (!node)
    return;

  --m_Size;

  Node *left = node->left;
  Node *right = node->right;

  if (!left && !right)
    m_Root = nullptr;
  else if (!left)
    transplant(node, right);
  else if (!right)
    transplant(node, left);
  else
    merge(node->left, node->right);

  node->left = nullptr;
  node->right = nullptr;

  delete node;
}

template<typename Key, typename Value>
Value &SplayTree<Key, Value>::operator[](const Key &key) {
  return insert(key, Value());
}

template<typename Key, typename Value>
typename SplayTree<Key, Value>::Node *SplayTree<Key, Value>::getMinNode(Node *node) const {
  while (node && node->left)
    node = node->left;

  return node;
}

template<typename Key, typename Value>
typename SplayTree<Key, Value>::Node *SplayTree<Key, Value>::getMaxNode(Node *node) const {
  while (node && node->right)
    node = node->right;

  return node;
}

template<typename Key, typename Value>
typename SplayTree<Key, Value>::Node *SplayTree<Key, Value>::getNode(const Key &key) {
  Node *node = m_Root;

  while (node && key != node->pair.first)
    node = node->pair.first > key ? node->left : node->right;

  if (node)
    splay(node);

  return node;
}

template<typename Key, typename Value>
typename SplayTree<Key, Value>::Node *SplayTree<Key, Value>::getRoot() {
  return m_Root;
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::transplant(Node *parent, Node *child) {
  if (!parent->parent)
    m_Root = child;
  else if (parent == parent->parent->left)
    parent->parent->left = child;
  else if (parent == parent->parent->right)
    parent->parent->right = child;

  if (child)
    child->parent = parent->parent;
}

template<typename Key, typename Value>
typename SplayTree<Key, Value>::Node *SplayTree<Key, Value>::rotateLeft(Node *node) {
  Node *right = node->right;
  Node *rightLeft = right->left;

  right->parent = node->parent;

  if (!node->parent)
    m_Root = right;
  else if (node == node->parent->left)
    node->parent->left = right;
  else
    node->parent->right = right;

  node->parent = right;
  right->left = node;
  node->right = rightLeft;

  if (rightLeft)
    rightLeft->parent = node;

  return right;
}

template<typename Key, typename Value>
typename SplayTree<Key, Value>::Node *SplayTree<Key, Value>::rotateRight(Node *node) {
  Node *left = node->left;
  Node *leftRight = left->right;

  left->parent = node->parent;

  if (!node->parent)
    m_Root = left;
  else if (node == node->parent->left)
    node->parent->left = left;
  else
    node->parent->right = left;

  node->parent = left;
  left->right = node;
  node->left = leftRight;

  if (leftRight)
    leftRight->parent = node;

  return left;
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::zig(Node *node) {
  m_Root = m_Root->left == node ? rotateRight(m_Root) : rotateLeft(m_Root);
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::zigZig(Node *node) {
  Node *parent = node->parent;
  Node *grandParent = parent->parent;

  if (parent->left == node && grandParent->left == parent) {
    if (grandParent == m_Root) {
      m_Root = rotateRight(m_Root);
      m_Root = rotateRight(m_Root);
      return;
    }

    node->parent = rotateRight(grandParent);
    node = rotateRight(node->parent);

    return splay(node);
  }

  if (parent->right == node && grandParent->right == parent) {
    if (grandParent == m_Root) {
      m_Root = rotateLeft(m_Root);
      m_Root = rotateLeft(m_Root);
      return;
    }

    node->parent = rotateLeft(grandParent);
    node = rotateLeft(node->parent);

    return splay(node);
  }
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::zigZag(Node *node) {
  Node *parent = node->parent;
  Node *grandParent = parent->parent;

  if (parent->right == node && grandParent->left == parent) {
    node = rotateLeft(parent);
    parent = node->parent;

    if (parent == m_Root) {
      m_Root = rotateRight(m_Root);
      return;
    }

    node = rotateRight(parent);

    return splay(node);
  }

  if (parent->left == node && grandParent->right == parent) {
    node = rotateRight(parent);
    parent = node->parent;

    if (parent == m_Root) {
      m_Root = rotateLeft(m_Root);
      return;
    }

    node = rotateLeft(parent);

    return splay(node);
  }
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node *node) {
  if (node == m_Root || !node)
    return;

  Node *parent = node->parent;
  Node *grandParent = parent->parent;

  if (parent == m_Root)
    return zig(node);

  if (parent->left == node && grandParent->left == parent ||
      parent->right == node && grandParent->right == parent)
    return zigZig(node);

  if (parent->right == node && grandParent->left == parent ||
      parent->left == node && grandParent->right == parent)
    return zigZag(node);
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::merge(Node *left, Node *right) {
  Node *leftMax = getMaxNode(left);

  splay(leftMax);

  leftMax->right = right;
  m_Root = leftMax;
}