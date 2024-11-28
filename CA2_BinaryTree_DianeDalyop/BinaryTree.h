#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#endif // BINARY_TREE_H

#include "BSTNode.h"
#include <vector>
#include <utility> // For std::pair

template <class K, class V>
class BinaryTree {
    void addItemToArray(BSTNode<K, V>* node, int& pos, std::pair<K, V>* arr);

public:
    BSTNode<K, V>* root;
    BinaryTree();
    BinaryTree(const BinaryTree<K, V>& other);
    BinaryTree<K, V> operator=(const BinaryTree<K, V>& other);
    void add(const std::pair<K, V>& item);  // Adding key-value pair
    bool remove(const std::pair<K, V>& item);  // Removing key-value pair
    void clear();
    int count();
    std::pair<K, V>& get(const K& key);  // Get value by key

    void printInOrder();
    void printInOrder(BSTNode<K, V>* node);
    void printPreOrder();
    void printPreOrder(BSTNode<K, V>* node);
    void printPostOrder();
    void printPostOrder(BSTNode<K, V>* node);
    std::pair<K, V>* toArray();
    ~BinaryTree();
};

template <class K, class V>
BinaryTree<K, V>::BinaryTree() {
    root = nullptr;
}

template <class K, class V>
BinaryTree<K, V>::BinaryTree(const BinaryTree<K, V>& other) {
    root = nullptr;
    if (other.root != nullptr)
        root = new BSTNode<K, V>(*other.root);
}

template <class K, class V>
BinaryTree<K, V> BinaryTree<K, V>::operator=(const BinaryTree<K, V>& other) {
    if (this == &other) return *this;
    if (other.root != nullptr)
        root = new BSTNode<K, V>(*other.root);
    else
        root = nullptr;
    return *this;
}

template <class K, class V>
void BinaryTree<K, V>::add(const std::pair<K, V>& item) {
    if (root == nullptr) {
        root = new BSTNode<K, V>(item);
    }
    else {
        root->add(item);
    }
}

template <class K, class V>
bool BinaryTree<K, V>::remove(const std::pair<K, V>& item) {
    BSTNode<K, V>* toBeRemoved = root;
    BSTNode<K, V>* parent = nullptr;
    bool found = false;

    while (!found && toBeRemoved != nullptr) {
        if (toBeRemoved->getKey() == item.first) {  // Compare the keys
            found = true;
        }
        else if (toBeRemoved->getKey() > item.first) {
            toBeRemoved = toBeRemoved->getLeft();
        }
        else {
            toBeRemoved = toBeRemoved->getRight();
        }
    }

    if (!found)
        return false;

    if (toBeRemoved->getLeft() == nullptr || toBeRemoved->getRight() == nullptr) {
        BSTNode<K, V>* newChild;
        if (toBeRemoved->getLeft() == nullptr) {
            newChild = toBeRemoved->getRight();
        }
        else {
            newChild = toBeRemoved->getLeft();
        }
        if (parent == nullptr) {
            root = newChild;
        }
        else if (parent->getLeft() == toBeRemoved) {
            parent->setLeft(newChild);
        }
        else {
            parent->setRight(newChild);
        }
        return true;
    }

    BSTNode<K, V>* smallestParent = toBeRemoved;
    BSTNode<K, V>* smallest = toBeRemoved->getRight();
    while (smallest->getLeft() != nullptr) {
        smallestParent = smallest;
        smallest = smallest->getLeft();
    }
    toBeRemoved->setItem(smallest->getItem());  // Copy the smallest value into toBeRemoved
    if (smallestParent == toBeRemoved) {
        smallestParent->setRight(smallest->getRight());
    }
    else {
        smallestParent->setLeft(smallest->getRight());
    }
    return true;
}

template <class K, class V>
std::pair<K, V>& BinaryTree<K, V>::get(const K& key) {
    BSTNode<K, V>* current = root;
    while (current != nullptr) {
        if (current->getKey() == key)
            return current->getItem();  // Return the key-value pair
        else if (current->getKey() > key)
            current = current->getLeft();
        else
            current = current->getRight();
    }
    throw std::logic_error("Item not found");
}

template <class K, class V>
void BinaryTree<K, V>::addItemToArray(BSTNode<K, V>* node, int& pos, std::pair<K, V>* arr) {
    if (node != nullptr) {
        addItemToArray(node->getLeft(), pos, arr);
        arr[pos] = node->getItem();
        pos++;
        addItemToArray(node->getRight(), pos, arr);
    }
}

template <class K, class V>
std::pair<K, V>* BinaryTree<K, V>::toArray() {
    std::pair<K, V>* arr = new std::pair<K, V>[root->count()];
    int pos = 0;
    addItemToArray(root, pos, arr);
    return arr;
}

template <class K, class V>
void BinaryTree<K, V>::clear() {
    if (root != nullptr) {
        delete root;
        root = nullptr;
    }
}

template <class K, class V>
BinaryTree<K, V>::~BinaryTree() {
    if (root != nullptr) {
        delete root;
        root = nullptr;
    }
}

// Print methods (you can implement as needed)
template <class K, class V>
void BinaryTree<K, V>::printInOrder() {
    printInOrder(root);
    std::cout << std::endl;
}

template <class K, class V>
void BinaryTree<K, V>::printInOrder(BSTNode<K, V>* node) {
    if (node != nullptr) {
        printInOrder(node->getLeft());
        std::cout << node->getKey() << " - " << node->getValue() << std::endl;  // Print key-value
        printInOrder(node->getRight());
    }
}

template <class K, class V>
void BinaryTree<K, V>::printPreOrder() {
    printPreOrder(root);
    std::cout << std::endl;
}

template <class K, class V>
void BinaryTree<K, V>::printPreOrder(BSTNode<K, V>* node) {
    if (node != nullptr) {
        std::cout << node->getKey() << " - " << node->getValue() << std::endl;
        printPreOrder(node->getLeft());
        printPreOrder(node->getRight());
    }
}

template <class K, class V>
void BinaryTree<K, V>::printPostOrder() {
    printPostOrder(root);
    std::cout << std::endl;
}

template <class K, class V>
void BinaryTree<K, V>::printPostOrder(BSTNode<K, V>* node) {
    if (node != nullptr) {
        printPostOrder(node->getLeft());
        printPostOrder(node->getRight());
        std::cout << node->getKey() << " - " << node->getValue() << std::endl;
    }
}
