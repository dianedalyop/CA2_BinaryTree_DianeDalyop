#pragma once
#include <iostream>

template <typename K, typename V>
class EntityKeyPair {
private:
    K key; // The key
    V value; // The value


public:
    // Default constructor
    EntityKeyPair() : key(K()), value(V()) {}

    // Parameterized constructor
    EntityKeyPair(K key, V value) : key(key), value(value) {}

    // Getter for the key
    K getKey() const {
        return key;
    }

    // Getter for the value
   

    V& getValue() { return value; } 


    const V& getValue() const { return value; }   


    // Setter for the key
    void setKey(K key) {

        this->key = key;
    }

    // Setter for the value
    void setValue(V value) {
        this->value = value;
    }

    // Overload the < operator for sorting in BST
    bool operator<(const EntityKeyPair& other) const {
        return key < other.key;
    }

    // Overload the == operator for equality comparison
    bool operator==(const EntityKeyPair& other) const {
        return key == other.key;
    }

    // Display the key-value pair (useful for debugging)
    friend std::ostream& operator<<(std::ostream& os, const EntityKeyPair<K, V>& pair) {
        os << "[" << pair.key << ": " << pair.value << "]";
        return os;
    }

};