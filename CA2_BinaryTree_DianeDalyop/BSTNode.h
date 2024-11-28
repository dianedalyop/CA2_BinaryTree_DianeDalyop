#pragma once
#include <iostream>
#include <utility>  // For std::pair

using namespace std;

template <class K, class V>
class BSTNode {
    BSTNode<K, V>* parent;
    BSTNode<K, V>* left;
    BSTNode<K, V>* right;
    std::pair<K, V> data;  // Key-value pair

public:
    BSTNode();
    BSTNode(const BSTNode<K, V>& other);
    BSTNode<K, V>* operator=(const BSTNode<K, V>& other);
    BSTNode(std::pair<K, V> data);

    void setItem(std::pair<K, V> item);
    std::pair<K, V>& getItem();  // Return reference to pair
    K getKey();  // Get key from pair
    V getValue();  // Get value from pair

    int count();
    void add(const std::pair<K, V>& item);  // Add key-value pair

    BSTNode<K, V>* getParent();
    BSTNode<K, V>* getLeft();
    BSTNode<K, V>* getRight();
    void setLeft(BSTNode<K, V>* l);
    void setRight(BSTNode<K, V>* r);

    ~BSTNode();
};

template <class K, class V>
BSTNode<K, V>::BSTNode(const BSTNode<K, V>& other) {
    left = right = nullptr;
    data = other.data;  // Copy the key-value pair
    if (other.left != nullptr)
        this->left = new BSTNode<K, V>(*other.left);
    if (other.right != nullptr)
        this->right = new BSTNode<K, V>(*other.right);
}

template <class K, class V>
BSTNode<K, V>* BSTNode<K, V>::operator=(const BSTNode<K, V>& other) {
    if (this == &other) return this;

    delete left;
    delete right;
    left = right = nullptr;

    data = other.data;  // Copy the key-value pair
    if (other.left != nullptr)
        this->left = new BSTNode<K, V>(*other.left);
    if (other.right != nullptr)
        this->right = new BSTNode<K, V>(*other.right);

    return this;
}

template <class K, class V>
BSTNode<K, V>::~BSTNode() {
    if (left != nullptr) {
        delete left;
        left = nullptr;
    }
    if (right != nullptr) {
        delete right;
        right = nullptr;
    }
}

template <class K, class V>
BSTNode<K, V>::BSTNode() {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

template <class K, class V>
BSTNode<K, V>::BSTNode(std::pair<K, V> data) {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    this->data = data;
}

template <class K, class V>
void BSTNode<K, V>::setItem(std::pair<K, V> item) {
    this->data = item;
}

template <class K, class V>
std::pair<K, V>& BSTNode<K, V>::getItem() {
    return this->data;
}

template <class K, class V>
K BSTNode<K, V>::getKey() {
    return this->data.first;
}

template <class K, class V>
V BSTNode<K, V>::getValue() {
    return this->data.second;
}

template <class K, class V>
int BSTNode<K, V>::count() {
    int c = 1;
    if (left != nullptr) {
        c += left->count();
    }
    if (right != nullptr) {
        c += right->count();
    }
    return c;
}

template <class K, class V>
void BSTNode<K, V>::add(const std::pair<K, V>& item) {
    if (item.first == this->data.first) {  // Check if the key already exists
        return;  // Do not insert duplicate keys
    }
    else if (item.first < this->data.first) {  // Compare keys
        if (left == nullptr) {
            left = new BSTNode<K, V>(item);
            left->parent = this;
        }
        else {
            left->add(item);
        }
    }
    else {
        if (right == nullptr) {
            right = new BSTNode<K, V>(item);
            right->parent = this;
        }
        else {
            right->add(item);
        }
    }
}

template <class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getParent() {
    return this->parent;
}

template <class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getLeft() {
    return this->left;
}

template <class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getRight() {
    return this->right;
}

template <class K, class V>
void BSTNode<K, V>::setLeft(BSTNode<K, V>* l) {
    this->left = l;
}

template <class K, class V>
void BSTNode<K, V>::setRight(BSTNode<K, V>* r) {
    this->right = r;
}
