// CA2_BinaryTree_DianeDalyop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "BinaryTree.h"
#include "BSTNode.h"

#include "EntityKeyPair.h"
// 
int main() {

    BinaryTree<int, std::string> mytree;
    
    std::string value1 = "";
    mytree.add(1, "apple");

    
    mytree.add(2, "orange");
    mytree.add(3, "Kiwi");
    mytree.add(4, "Banana");
    mytree.add(5, "Peach");


    
    mytree.printInOrder();

    // testing clear implementation 
// Clear the tree
    mytree.clear();

    //  tree after clearing
    std::cout << "Tree after clearing:" << std::endl;

    mytree.printInOrder();

    std::cout << "Adding new tree Items: " << std::endl;
    
    mytree.add(1, "apple");


    mytree.add(2, "orange");
    mytree.add(3, "Mango");
    mytree.add(4, "Banana");
    mytree.add(5, "Peach");
    mytree.printInOrder();

    // existing and non-existing keys
    std::cout << " key 2 exist? " << (mytree.containsKey(2) ? "Yes" : "No") << std::endl; 
    std::cout << " key 10 exist? " << (mytree.containsKey(10) ? "Yes" : "No") << std::endl; 

    // value for existing keys 

    std::cout << "Value for key 2: " << mytree.getKeyValue(2) << std::endl;
    // value for non - existing keys 
    try {
        std::cout << "Value for key 10: " << mytree.getKeyValue(10) << std::endl; 
    }
    catch (const std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }

    // fetching  keys

    BinaryTree<int, int> mykeySet = mytree.keySet();  
    std::cout << "" << endl;
    std::cout << "Existing Keys"<< endl;
    mykeySet.printInOrder();

    return 0;
}

