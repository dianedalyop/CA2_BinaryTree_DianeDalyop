#pragma once
#include <iostream>
#include "EntityKeyPair.h"

using namespace std;

template <class T>
class BSTNode
{
    BSTNode<T>* parent;
    BSTNode<T>* left;
    BSTNode<T>* right;
    T data;

public:
    BSTNode();
    BSTNode(const BSTNode<T>& other);
    BSTNode<T>* operator=(const BSTNode<T>& other);
    BSTNode(T data);
    void setItem(T item);
    int count();
    void add(T& item);
    BSTNode<T>* getParent();
    BSTNode<T>* getLeft();
    BSTNode<T>* getRight();
    void setLeft(BSTNode<T>* l);
    void setRight(BSTNode<T>* r);
    T& getItem();
    ~BSTNode();
};

// Constructor
template <class T>
BSTNode<T>::BSTNode() : parent(nullptr), left(nullptr), right(nullptr), data(T()) {}

// Parameterized constructor
template <class T>
BSTNode<T>::BSTNode(T data) : parent(nullptr), left(nullptr), right(nullptr), data(data) {}

// Copy constructor
template <class T>
BSTNode<T>::BSTNode(const BSTNode<T>& other)
{
    left = right = nullptr;
    if (other.left != nullptr) {
        this->left = new BSTNode<T>(*other.left);
        this->left->parent = this;  // Set the parent for left child
    }
    if (other.right != nullptr) {
        this->right = new BSTNode<T>(*other.right);
        this->right->parent = this;  // Set the parent for right child
    }
    this->data = other.data;
}

// Assignment operator
template <class T>
BSTNode<T>* BSTNode<T>::operator=(const BSTNode<T>& other)
{
    if (this == &other)
        return *this;

    delete left;  // Delete current children to prevent memory leaks
    delete right;

    left = right = nullptr;
    if (other.left != nullptr) {
        this->left = new BSTNode<T>(*other.left);
        this->left->parent = this;
    }
    if (other.right != nullptr) {
        this->right = new BSTNode<T>(*other.right);
        this->right->parent = this;
    }
    this->data = other.data;

    return *this;
}

// Destructor
template <class T>
BSTNode<T>::~BSTNode()
{
    delete left;  // Delete left child
    delete right; // Delete right child
}

// Set item
template <class T>
void BSTNode<T>::setItem(T item)
{
    this->data = item;
}

// Count function
template <class T>
int BSTNode<T>::count()
{
    int c = 1;
    if (left != nullptr) {
        c += left->count();
    }
    if (right != nullptr) {
        c += right->count();
    }
    return c;
}

// Add function
template <class T>
void BSTNode<T>::add(T& item)
{
    if (item == this->data) {
        return; // No duplicates
    }
    else if (item < this->data) {
        if (left == nullptr) {
            left = new BSTNode<T>(item);
            left->parent = this;  // Set parent
        }
        else {
            left->add(item); // Recursively add to left
        }
    }
    else {
        if (right == nullptr) {
            right = new BSTNode<T>(item);
            right->parent = this;  // Set parent
        }
        else {
            right->add(item); // Recursively add to right
        }
    }
}

// Getters for left, right, and parent
template <class T>
BSTNode<T>* BSTNode<T>::getParent()
{
    return this->parent;
}

template <class T>
BSTNode<T>* BSTNode<T>::getLeft()
{
     return this->left;
}

template <class T>
BSTNode<T>* BSTNode<T>::getRight()
{
    return this->right;
}

// Setters for left and right children
template <class T>
void BSTNode<T>::setLeft(BSTNode<T>* l)
{
    this->left = l;
}

template <class T>
void BSTNode<T>::setRight(BSTNode<T>* r)
{
    this->right = r;
}

// Getter for the item
template <class T>
T& BSTNode<T>::getItem()
{
    return this->data;
}
