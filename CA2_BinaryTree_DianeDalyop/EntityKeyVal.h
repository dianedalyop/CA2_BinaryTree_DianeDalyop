#pragma once
#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

template <typename K, typename V>
class KeyValuePair {
public:
    K key;
    V value;

    // Constructor
    KeyValuePair(K key, V value) : key(key), value(value) {}

    // Overload equality operator for comparison 
    bool operator==(const KeyValuePair<K, V>& other) const {
        return key == other.key && value == other.value;
    }

    // Overload less-than operator for sorting by key
    bool operator<(const KeyValuePair<K, V>& other) const {
        return key < other.key;
    }

    
    void display() const {
        std::cout << "{" << key << ": " << value << "}";
    }
};

#endif // KEYVALUEPAIR_H
