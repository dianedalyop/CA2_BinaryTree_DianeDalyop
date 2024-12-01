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
    const K& getKey() const { return key; }

    // Getter for the value
    V& getValue() { return value; }
    const V& getValue() const { return value; }

    // Setter for the key
    void setKey(K key) { this->key = key; }

    // Setter for the value
    void setValue(const V& val) { value = val; }

    // Overload the == operator for equality comparison
    bool operator==(const EntityKeyPair& other) const {
        return key == other.key;
    }

    // Less-than operator
    bool operator<(const EntityKeyPair& other) const {
        return key < other.key;
    }
};

// Generic operator<< for other types of V
template <class K, class V>
inline std::ostream& operator<<(std::ostream& os, const EntityKeyPair<K, V>& pair) {
    os << pair.getKey() << ": " << pair.getValue();
    return os;
}

// Specialization for nullptr_t as value type (V)
template <class K>
inline std::ostream& operator<<(std::ostream& os, const EntityKeyPair<K, std::nullptr_t>& pair) {
    os << pair.getKey() << ": null";  // Print "null" for nullptr_t
    return os;
}
