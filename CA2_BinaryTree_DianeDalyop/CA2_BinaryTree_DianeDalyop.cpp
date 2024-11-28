// CA2_BinaryTree_DianeDalyop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "BinaryTree.h";
// 
int main() {
    BSTNode<int, std::string> root(std::make_pair(1, "Apple"));
    root.add(std::make_pair(2, "Banana"));
    root.add(std::make_pair(3, "Cherry"));

    std::cout << "Root Item: " << root.getItem().first << " - " << root.getItem().second << std::endl;  
    std::cout << "Left Item: " << root.getLeft()->getItem().first << " - " << root.getLeft()->getItem().second << std::endl; 
    std::cout << "Right Item: " << root.getRight()->getItem().first << " - " << root.getRight()->getItem().second << std::endl;  

    return 0;
}

