// CA2_BinaryTree_DianeDalyop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Song.h"
using namespace std;
#include "BinaryTree.h"
#include "BSTNode.h"

#include "EntityKeyPair.h"
// 
int main() {

	BinaryTree<int, std::string> mytree;
	BinaryTree<int, int> mykeySet = mytree.keySet();
	BinaryTree<char, BinaryTree<std::string, std::nullptr_t>> letterTree;
	std::string filename = "Song_Dataset.csv";
	std::vector<Song> songs = parseCSV(filename);
	int choice;

	do {

		std::cout << "\nBinary Tree Menu:\n";
		
		std::cout << "1. Add new items to the tree\n";
		std::cout << "2. Clear\n";
		std::cout << "3. Adding new tree items\n";
		std::cout << "4. Displaying Existing Keys\n";
		std::cout << "5. Display value for keys\n";
		std::cout << "6. Display all current keys\n";
		std::cout << "7. Putting tree function\n";
		std::cout << "8. Display tree size\n";
		std::cout << "9. Removing A key\n";
		std::cout << "10.Key and Value\n";
		std::cout << "11. Load words From text file\n";
		std::cout << "12. Get songs dataset\n";
		std::cout << "0. Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			mytree.add(1, "apple");


			mytree.add(2, "orange");
			mytree.add(3, "Kiwi");
			mytree.add(4, "Banana");
			mytree.add(5, "Peach");
			std::cout << "Items added.\n";


			mytree.printInOrder();
			break;

		case 2:

			// testing clear implementation 
		// Clear the tree
			mytree.clear();
			std::cout << "Tree after clearing:" << std::endl;

			mytree.printInOrder();
			break;

		case 3:

			std::cout << "Adding new tree Items: " << std::endl;

			mytree.add(1, "apple");


			mytree.add(2, "orange");
			mytree.add(3, "Mango");
			mytree.add(4, "Banana");
			mytree.add(5, "Peach");
			mytree.printInOrder();
			break;

		case 4:
			// existing and non-existing keys
			std::cout << " key 2 exist? " << (mytree.containsKey(2) ? "Yes" : "No") << std::endl;
			std::cout << " key 10 exist? " << (mytree.containsKey(10) ? "Yes" : "No") << std::endl;
			break;

		case 5:
			// value for existing keys 

			std::cout << "Value for key 2: " << mytree.getKeyValue(2) << std::endl;
			// value for non - existing keys 
			try {
				std::cout << "Value for key 10: " << mytree.getKeyValue(10) << std::endl;
			}
			catch (const std::logic_error& e) {
				std::cerr << e.what() << std::endl;
			}
			break;

		case 6:
			// fetching  keys

			std::cout << "" << endl;
			std::cout << "Existing Keys" << endl;
			mykeySet.printInOrder();
			break;

		case 7:
			// put function application
			std::cout << "Before put function \n";
			mytree.printInOrder();

			mytree.put(2, "Avocado");
			mytree.put(4, "banana");
			mytree.put(6, "pears");


			std::cout << "After put function \n";
			mytree.printInOrder();

		case 8:
			std::cout << "Tree Size : " << mytree.size() << std::endl;

			break;

		case 9:
			// Remove a key-value pair
			std::cout << "\nRemoving key 6:\n";
			mytree.removeKey(6);


			std::cout << "\nAfter removing key 6:\n";
			mytree.printInOrder();

			break;

		case 10:
			// operator values
			std::cout << "key 1 value: " << mytree[1] << std::endl;
			std::cout << "Key 2 value: " << mytree[2] << std::endl;


			try {
				std::cout << "Key 7 value : " << mytree[7] << std::endl;
			}
			catch (const std::logic_error& e) {
				std::cout << "Error: " << e.what() << std::endl;
			}
			break;
			// stage 2 

		case 11:
			// Treemap to store letters and words



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

			break;

		case 12:


			if (songs.empty()) {
				std::cout << "No data found in the CSV file." << std::endl;
				return 0;
			}

			// Display a few records for testing
			std::cout << "Parsed Song Records:\n";
			for (size_t i = 0; i < std::min(songs.size(), size_t(5)); ++i) {
				const auto& song = songs[i];
				std::cout << "Song: " << song.song
					<< ", Artist: " << song.artist
					<< ", Genre: " << song.genre
					<< ", Downloads: " << song.downloads
					<< ", Awards: " << song.awards
					<< ", Streams: " << song.streams << '\n';
			}
			break;

		case 0: // Exit
			std::cout << "Exiting program.\n";
			break;

		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 0);

	return 0;
}

