#pragma once
#include <iostream>
#include <stdexcept>
#include "BSTNode.h"
#include "EntityKeyPair.h"
#include <vector>
#include <string>

template <class K, class V>
class BinaryTree
{
    void addItemToArray(BSTNode<EntityKeyPair<K, V>>* node, int& pos, EntityKeyPair<K, V>* arr);

public:
    BSTNode<EntityKeyPair<K, V>>* root;

   
    /// Constructor
    BinaryTree();
    BinaryTree(const BinaryTree<K, V>& other);
    BinaryTree<K, V>& operator=(const BinaryTree<K, V>& other);
    ~BinaryTree(); // Destructor

    /// Main functions
    void add(const K& key, const V& value);
    bool remove(const K& key);
    void clear(); // Clears the entire tree
    int count();
    V& get(const K& key);
    V& getKeyValue(const K& key);
    bool containsKey(K key);
    BinaryTree<K, int> keySet(); // Declare keySet method to return BinaryTree with int (for keys)

    void collectKeys(BSTNode<EntityKeyPair<K, V>>* node, BinaryTree<K, int>& keyTree); // Helper for keySet

    void printInOrder();
    void printInOrder(BSTNode<EntityKeyPair<K, V>>* node);
    void printPreOrder();
    void printPreOrder(BSTNode<EntityKeyPair<K, V>>* node);
    void printPostOrder();
    void printPostOrder(BSTNode<EntityKeyPair<K, V>>* node);

    EntityKeyPair<K, V>* toArray();
};

// Constructor
template <class K, class V>
BinaryTree<K, V>::BinaryTree()
{
    root = nullptr;
}

// Copy Constructor
template <class K, class V>
BinaryTree<K, V>::BinaryTree(const BinaryTree<K, V>& other)
{
    root = nullptr;
    if (other.root != nullptr)
        root = new BSTNode<EntityKeyPair<K, V>>(*other.root);
}

// Assignment Operator
template <class K, class V>
BinaryTree<K, V>& BinaryTree<K, V>::operator=(const BinaryTree<K, V>& other)
{
    if (this == &other)
        return *this;

    clear(); // Clear current tree
    if (other.root != nullptr)
        root = new BSTNode<EntityKeyPair<K, V>>(*other.root);

    return *this;
}

// Destructor
template <class K, class V>
BinaryTree<K, V>::~BinaryTree()
{
    clear(); // Clears the tree to release memory
}

// Clear Function
template <class K, class V>
void BinaryTree<K, V>::clear()
{
    delete root;   
    root = nullptr; 
}

// Add Function
template <class K, class V>
void BinaryTree<K, V>::add(const K& key, const V& value)
{
    EntityKeyPair<K, V> pair(key, value);
    if (root == nullptr)
    {
        root = new BSTNode<EntityKeyPair<K, V>>(pair);
    }
    else
    {
        root->add(pair);
    }
}

// Remove Function
template <class K, class V>
bool BinaryTree<K, V>::remove(const K& key)
{
    EntityKeyPair<K, V> searchKey(key, V());
    BSTNode<EntityKeyPair<K, V>>* toBeRemoved = root;
    BSTNode<EntityKeyPair<K, V>>* parent = nullptr;
    bool found = false;

    // find the node to remove
    while (!found && toBeRemoved != nullptr) {
        if (toBeRemoved->getItem() == searchKey) {
            found = true;
        }
        else {
            parent = toBeRemoved;
            if (searchKey < toBeRemoved->getItem()) {
                toBeRemoved = toBeRemoved->getLeft();
            }
            else {
                toBeRemoved = toBeRemoved->getRight();
            }
        }
    }

    if (!found) return false; // Node not found

    // Node has no children
    if (toBeRemoved->getLeft() == nullptr && toBeRemoved->getRight() == nullptr) {
        if (parent == nullptr) { // Removing root node
            root = nullptr;
        }
        else if (parent->getLeft() == toBeRemoved) {
            parent->setLeft(nullptr);
        }
        else {
            parent->setRight(nullptr);
        }
        delete toBeRemoved;
        return true;
    }

    //  Node has one child
    if (toBeRemoved->getLeft() == nullptr || toBeRemoved->getRight() == nullptr) {
        BSTNode<EntityKeyPair<K, V>>* child = (toBeRemoved->getLeft() == nullptr)
            ? toBeRemoved->getRight()
            : toBeRemoved->getLeft();

        if (parent == nullptr) { 
            root = child;
        }
        else if (parent->getLeft() == toBeRemoved) {
            parent->setLeft(child);
        }
        else {
            parent->setRight(child);
        }
        delete toBeRemoved;
        return true;
    }

    //  Node has two children
    BSTNode<EntityKeyPair<K, V>>* smallestParent = toBeRemoved;
    BSTNode<EntityKeyPair<K, V>>* smallest = toBeRemoved->getRight();
    while (smallest->getLeft() != nullptr) {  
        smallestParent = smallest;
        smallest = smallest->getLeft();
    }

    // Replace current node's data with the smallest node (in-order successor)
    toBeRemoved->setItem(smallest->getItem());

    // Remove the in-order successor
    if (smallestParent->getLeft() == smallest) {
        smallestParent->setLeft(smallest->getRight());
    }
    else {
        smallestParent->setRight(smallest->getRight());
    }
    delete smallest;
    return true;
}

// Get Function
template <class K, class V>
V& BinaryTree<K, V>::get(const K& key)
{
    EntityKeyPair<K, V> searchKey(key, V());
    BSTNode<EntityKeyPair<K, V>>* current = root;

    while (current != nullptr)
    {
        if (current->getItem() == searchKey)
            return current->getItem().getValue();
        else if (searchKey < current->getItem())
            current = current->getLeft();
        else
            current = current->getRight();
    }

    throw std::logic_error("Key not found!");
}

// Count Function
template <class K, class V>
int BinaryTree<K, V>::count()
{
    if (root == nullptr)
        return 0;
    return root->count();
}

// Traversals
template <class K, class V>
void BinaryTree<K, V>::printInOrder()
{
    printInOrder(root);
    std::cout << std::endl;
}

template <class K, class V>
void BinaryTree<K, V>::printInOrder(BSTNode<EntityKeyPair<K, V>>* node)
{
    if (node == nullptr) return;

    printInOrder(node->getLeft());
    std::cout << node->getItem().getKey() << ": " << node->getItem().getValue() << std::endl;
    printInOrder(node->getRight());
}
template <class K, class V>
void BinaryTree<K, V>::printPreOrder()
{
    printPreOrder(root);
    std::cout << std::endl;
}

template <class K, class V>
void BinaryTree<K, V>::printPreOrder(BSTNode<EntityKeyPair<K, V>>* node)
{
    if (node != nullptr)
    {
        std::cout << node->getItem().getKey() << ": " << node->getItem().getValue() << std::endl;
        printPreOrder(node->getLeft());
        printPreOrder(node->getRight());
    }
}

template <class K, class V>
void BinaryTree<K, V>::printPostOrder()
{
    printPostOrder(root);
    std::cout << std::endl;
}

template <class K, class V>
void BinaryTree<K, V>::printPostOrder(BSTNode<EntityKeyPair<K, V>>* node)
{
    if (node != nullptr)
    {
        printPostOrder(node->getLeft());
        printPostOrder(node->getRight());
        std::cout << node->getItem().getKey() << ": " << node->getItem().getValue() << std::endl;
    }
}

// Convert to Array
template <class K, class V>
EntityKeyPair<K, V>* BinaryTree<K, V>::toArray()
{
    int size = count();
    EntityKeyPair<K, V>* arr = new EntityKeyPair<K, V>[size];
    int pos = 0;
    addItemToArray(root, pos, arr);
    return arr;
}

// collecting keys
template <class K, class V>
void BinaryTree<K, V>::collectKeys(BSTNode<EntityKeyPair<K, V>>* node, BinaryTree<K, int>& keyTree)
{
    if (node == nullptr) {
        return; 
    }

    collectKeys(node->getLeft(), keyTree);         
    keyTree.add(node->getItem().getKey(), 0);          
    collectKeys(node->getRight(), keyTree);           
}

// keySet Function
template <class K, class V>
BinaryTree<K, int> BinaryTree<K, V>::keySet()
{
    BinaryTree<K, int> keyTree; // new binary tree to store keys
    collectKeys(root, keyTree); 
    return keyTree;
}




//GET VALUE OF KEY 
template <class K, class V>
V& BinaryTree<K, V> ::getKeyValue(const K& key)
{

    EntityKeyPair<K, V> keyToFind(key, V());
    BSTNode<EntityKeyPair<K, V>>* current = root;

    while (current != nullptr)
    {
    // if my key is found return the value for it
        if(current -> getItem() == keyToFind)

        {
           
            return current->getItem().getValue();
        }
        else if (key < current->getItem().getKey())
        {
            current = current->getLeft();
        }
        else
        {
            
            current = current->getRight();
        }
    }
    throw std::logic_error("Key could not be found!!!!");

}






// contains key 

template <class K, class V>
bool BinaryTree<K, V>::containsKey(K key)
{
    BSTNode<EntityKeyPair<K, V>>* current = root;

    while (current != nullptr) {
        if (key == current->getItem().getKey()) {
            return true;  
            // found
        }
        else if (key < current->getItem().getKey()) {
            current = current->getLeft();  //  left
        }
        else {
            current = current->getRight(); //  right
        }
    }

    return false; 
    // not found
}






