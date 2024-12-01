// CA2_BinaryTree_DianeDalyop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
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

    // put function application
    std::cout << "Before put function \n";
    mytree.printInOrder();

    mytree.put(2, "Avocado"); 
    mytree.put(4, "banana"); 
    mytree.put(6, "pears");

   
    std::cout << "After put function \n";
    mytree.printInOrder();


    std::cout << "Tree Size : " << mytree.size() << std::endl;

    // remove function

    // Remove a key-value pair
    std::cout << "\nRemoving key 6:\n";
    mytree.removeKey(6);

   
    std::cout << "\nAfter removing key 6:\n";
    mytree.printInOrder();


    // [operator values]
    std::cout << "key 1 value: " << mytree[1] << std::endl; 
    std::cout << "Key 2 value: " << mytree[2] << std::endl;  

   
    try {
        std::cout << "Key 7 value : " << mytree[7] << std::endl;  
    }
    catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << std::endl; 
    }

    // stage 2 

    
    // Treemap to store letters and words

    BinaryTree<char, BinaryTree<std::string, std::nullptr_t>> letterTree;

    try {
        letterTree.loadWordsFromFile("myfathersDragon.txt");

        std::cout << "File loaded successfully. Enter a letter to display words : \n";

        std::string input;
        while (true) {
            std::cout << "Enter a letter: ";
            std::cin >> input;

            if (input == "exit") break;

            if (input.length() == 1 && isalpha(input[0])) {
                char letter = std::tolower(input[0]);
                letterTree.printWordsByLetter(letter);
            }
            else {
                std::cout << "Invalid input. Please enter a single letter.\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}

