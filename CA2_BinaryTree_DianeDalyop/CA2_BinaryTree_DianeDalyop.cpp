// CA2_BinaryTree_DianeDalyop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "BinaryTree.h";
#include "BSTNode.h";
#include "EntityKeyVal.h";
// 
int main(){

    BinaryTree<int> mytree;
    mytree.add(2);
    mytree.add(8);
    cout << "Before clear: " << mytree.count() << endl;
    mytree.clear();
    cout << "After clear: " << mytree.count() << endl;



    return 0;
    
}

