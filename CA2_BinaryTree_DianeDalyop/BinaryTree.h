#pragma once
#include <iostream>
#include <stdexcept>
#include "BSTNode.h"
#include "EntityKeyPair.h"
#include <vector>
#include <string>

template <class K, class V = std::nullptr_t>
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

    
    bool removeKey(const K& key);
    void clear(); // Clears the entire tree
    int size();
    int count();
    V& operator[](K key);
    V& get(const K& key);
    V& getKeyValue(const K& key);
    bool containsKey(K key);
    BinaryTree<K, int> keySet(); 
    void loadWordsFromFile(const std::string& filename);

    void collectKeys(BSTNode<EntityKeyPair<K, V>>* node, BinaryTree<K, int>& keyTree); // Helper for keySet
    void put(K key, V value);
    void printInOrder();
    void printInOrder(BSTNode<EntityKeyPair<K, V>>* node);
    void printPreOrder();
    void printPreOrder(BSTNode<EntityKeyPair<K, V>>* node);
    void printPostOrder();
    void printPostOrder(BSTNode<EntityKeyPair<K, V>>* node);
    void printWordsByLetter(K letter);

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
// operator value function

template <class K, class V>
V& BinaryTree<K, V>::operator[](K key)
{
    EntityKeyPair<K, V> searchKey(key, V());  
    BSTNode<EntityKeyPair<K, V>>* current = root;

    
    while (current != nullptr)
    {
        if (current->getItem() == searchKey)
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

    // throw exception if key is not found
    throw std::logic_error("Key not found in the map!");
}


// Remove Function
// removeKey method to remove a node by key
template<class K, class V>
bool BinaryTree<K, V>::removeKey(const K& key)
{
   
    EntityKeyPair<K, V> searchKey(key, V());
    BSTNode<EntityKeyPair<K, V>>* toBeRemoved = root;
    BSTNode<EntityKeyPair<K, V>>* parent = nullptr;
    bool found = false;

    // node to remove by key
    while (toBeRemoved != nullptr) {
        if (toBeRemoved->getItem() == searchKey) {
            found = true;
            break;
        }
        parent = toBeRemoved;
        if (key < toBeRemoved->getItem().getKey()) {
            toBeRemoved = toBeRemoved->getLeft();
        }
        else {
            toBeRemoved = toBeRemoved->getRight();
        }
    }

   
    if (!found) {
        return false;
    }

    // 1: Node has no children (leaf node)
    if (toBeRemoved->getLeft() == nullptr && toBeRemoved->getRight() == nullptr) {
        if (parent == nullptr) {
            root = nullptr; // Root node
        }
        else if (parent->getLeft() == toBeRemoved) {
            parent->setLeft(nullptr); // Remove from left of parent
        }
        else {
            parent->setRight(nullptr); // Remove from right of parent
        }
        delete toBeRemoved; // Free the memory
        return true;
    }

    //  2: Node has one child
    if (toBeRemoved->getLeft() == nullptr || toBeRemoved->getRight() == nullptr) {
        BSTNode<EntityKeyPair<K, V>>* child = (toBeRemoved->getLeft() == nullptr)
            ? toBeRemoved->getRight()
            : toBeRemoved->getLeft();

        if (parent == nullptr) {
            root = child; // Root node with one child
        }
        else if (parent->getLeft() == toBeRemoved) {
            parent->setLeft(child); // Set parent's left child
        }
        else {
            parent->setRight(child); // Set parent's right child
        }
        delete toBeRemoved; // Free the memory
        return true;
    }

    //  3: Node has two children
   
    BSTNode<EntityKeyPair<K, V>>* smallestParent = toBeRemoved;
    BSTNode<EntityKeyPair<K, V>>* smallest = toBeRemoved->getRight();
    while (smallest->getLeft() != nullptr) {
        smallestParent = smallest;
        smallest = smallest->getLeft();
    }

  
    toBeRemoved->setItem(smallest->getItem());

   
    if (smallestParent->getLeft() == smallest) {
        smallestParent->setLeft(smallest->getRight());
    }
    else {
        smallestParent->setRight(smallest->getRight());
    }

    delete smallest; // Free the memory
    return true;
}
/// <summary>
/// loading words from file 
/// </summary>
/// <typeparam name="K"></typeparam>
/// <typeparam name="V"></typeparam>
/// <param name="filename"></param>
template <class K, class V>
void BinaryTree<K, V>::loadWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string word;
    while (file >> word) {
        char firstLetter = std::tolower(word[0]); 
        char key = firstLetter;                

       
        if (!this->containsKey(key)) {
            this->put(key, BinaryTree<std::string, std::nullptr_t>());
        }

        
        this->operator[](key).add(word, nullptr);
    }

    file.close();
}
// Print words by first letter
template <class K, class V>
void BinaryTree<K, V>::printWordsByLetter(K letter)
{
    BSTNode<EntityKeyPair<K, V>>* current = root;

    bool foundWords = false;

    while (current != nullptr)
    {
        if (current->getItem().getKey() == letter)
        {
            std::cout << "Words starting with '" << letter << "':\n";
            current->getItem().getValue().printInOrder();  // Assuming value is a BinaryTree with words
            return;
        }
        else if (letter < current->getItem().getKey())
        {
            current = current->getLeft();
        }
        else
        {
            current = current->getRight();
        }
    }

    std::cout << "No words found starting with '" << letter << "'.\n";
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


// size method 
template <class K, class V>
int BinaryTree<K, V>::size()
{
    return count(); 
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
    if (node != nullptr) {
        printInOrder(node->getLeft());
        std::cout << node->getItem() << std::endl;  // No ambiguity now
        printInOrder(node->getRight());
    }
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

// PUT METHOD 
template <class K, class V>
void BinaryTree<K, V>::put(K key, V value)
{
    EntityKeyPair<K, V> newPair(key, value);
    BSTNode<EntityKeyPair<K, V>>* current = root;
    BSTNode<EntityKeyPair<K, V>>* parent = nullptr;

    while (current != nullptr)
    {
        parent = current;
        if (key == current->getItem().getKey()) {
            //  if the Key  is found update the value
            current->getItem().setValue(value); 
            return;
        }
        else if (key < current->getItem().getKey()) {
            current = current->getLeft();
        }
        else {
            current = current->getRight();
        }
    }



    // if Key is not found, create and insert a new key-value pair
    if (parent == nullptr) {

        root = new BSTNode<EntityKeyPair<K, V>>(newPair);
    }
    else if (key < parent->getItem().getKey()) {
        parent->setLeft(new BSTNode<EntityKeyPair<K, V>>(newPair));
    }
    else {
        parent->setRight(new BSTNode<EntityKeyPair<K, V>>(newPair));
    }
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






