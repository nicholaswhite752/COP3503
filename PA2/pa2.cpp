#include <iostream>
#include <string>
#include "stdio.h"
#include "pa2.h"
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {

	//Makes sure a correct number of arguments is entered. If not exit.
	if (argc != 2) {
		std::cout << "Incorrect Arguments" << endl;
		exit(EXIT_SUCCESS);
	}

	//Checks which type of algorithm to run
	else if (string(argv[1]) == "worst") {
		std::cout << "Using worst fit algorithm" << endl;
	}
	else if (string(argv[1]) == "best") {
		std::cout << "Using best fit algorithm" << endl;
	}
	else {
		cout << "Invalid Input. Exiting Now." << endl;
		exit(EXIT_SUCCESS);
	}

	std::cout << endl;

	//Creates Linked List
	LinkedList LL;

	//Populates List with Free
	for (int i = 0; i < 32; i++) {
		LL.createInitial("Free");
	}

	//Menu creation
	std::cout << "\t" << "1. Add a program" << endl;
	std::cout << "\t" << "2. Kill a program" << endl;
	std::cout << "\t" << "3. Fragmentation" << endl;
	std::cout << "\t" << "4. Print memory" << endl;
	std::cout << "\t" << "5. Exit" << endl;
	std::cout << endl;

	//Initializes variables used in the choices
	int choice;
	string name = "";
	int size;
	int pageNum;

	do {

		std::cout << "choice - ";
		cin >> choice;

		//Stops an infinte loop from occuring if a letter is put in
		cin.clear();
		std::cin.ignore(1000, '\n');
		
		if (choice == 1) {

			cout << "Program name - ";
			cin >> name;

			//Exits program if "Free" is put into the program name.
			if (name == "Free") {
				cout << "Not a valid Program Name. Exiting." << endl;
				exit(EXIT_SUCCESS);
			}

			while (true) {
				double tempSize = 0;
				cout << "Program Size (KB) - ";
				cin >> tempSize;
				
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				
				//Checks for decimal input
				if (tempSize != (int)tempSize) {
					std::cout << "Do not enter decimals" << endl;
					continue;
				}
				//Checks for string input
				if (tempSize == 0) {
					std::cout << "Invalid Input" << endl;
					continue;
				}

				else {
					size = tempSize;
					break;
				}

			}
			//Takes the size and divides by four to get the number of pages taken.
			pageNum = ceil((double)size / 4);


			if (string(argv[1]) == "worst") {
				//Worst fit equals true
				if (LL.worstFit(name, pageNum)) {
					//Uses the replace method to put in the "program" in the correct placement per the algorithm.
					for (int i = LL.worst; i < (LL.worst + pageNum); i++) {
						LL.replace(name, i);
					}
					cout << "Program " << name << " added successully " << pageNum << " page(s) used."<<endl;
				}

				else {

				}
			}

			else {

				if (string(argv[1]) == "best") {
					//Makes sure best fit is true
					if (LL.bestFit(name, pageNum)) {
						//Uses the replace method to put in the "program" in the correct placement per the algorithm.
						for (int i = LL.best; i < (LL.best+pageNum); i++) {
							LL.replace(name, i);
						}


						cout << "Program " << name << " added successully " << pageNum << " page(s) used."<< endl;
					}
					else {

					}
				}

			}
		}//ends choice 1

		else if (choice == 2) {
			cout << "Program - ";
			cin >> name;

			//Exits program if the "Free" program is deleted
			if (name == "Free") {
				std::cout << "Not a valid name. Exiting" << endl;
				exit(EXIT_SUCCESS);
			}

			//Uses the remove method to remove programs and report the number of pages back
			if (LL.remove(name)) {
				std::cout << "Program " << name << " killed, " << LL.pagesRemoved << " pages reclaimed." << endl;
			}
			else {
				std::cout << "Program " << name << " does not exist and cannot be killed." << endl;
			}

		}//ends 2

		//Prints fragmentation
		else if (choice == 3) {
			LL.printFrag();
		}//end 3

		//Prints the Linked List
		else if (choice == 4) {
			LL.printLL();
		}//end 4

		//Exits
		else if (choice == 5) {
			exit(EXIT_SUCCESS);
		}//end 5

		//Error message if an invalid option is entered
		else{
			std::cout << "Pleases enter a valid menu option." << endl;
		}

	cout << endl;
	}

	//Does the loop until the exit option is entered
	while (choice != 5);

	return 0;

}