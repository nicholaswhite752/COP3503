#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class LinkedList {

private:
	//Creates a node using a c++ structure
	typedef struct node {
		string data;
		node* next;
		bool isOpen;

	}*nodePtr;

	//Node pointers used for parsing the Linked List
	nodePtr head;
	nodePtr current;
	nodePtr temp;

public:
	//Methods and Constructors
	LinkedList() {};
	void createInitial(string insertedData);
	void printLL();
	bool bestFit(string insertedData, int size);
	int best;
	bool worstFit(string insertedData, int size);
	int worst;
	void replace(string insertedData, int size);
	bool remove(string insertedData);
	int pagesRemoved;
	void printFrag();



};

//Creates the initial Linked List
//In the main program the word "Free" is ran through the method to create the 
//intial Linked List with 32 free spots
void LinkedList::createInitial(string data) {
	//Creates a node to start the list
	nodePtr n = new node;
	n->next = NULL;
	n->data = data;

	//Checks of head is null, if not it makes the current node equal to the head node
	if (head != NULL) {
		current = head;
		while (current->next != NULL) {
			current = current->next;

		}
		current->next = n;
	}
	//if not the head equals the original node created
	else {
		head = n;
	}
};

//Checks to see if the best fit is a viable option to insert the specified program
bool LinkedList::bestFit(string inserted, int size) {
	//Intializes variables need for the method

	//When I set counter equal to 0, the program would only populate 30 out of 32 blocks
	//For counter=2 it would populate all 32 blocks, I am not completely sure why my counting was orignally off by two.
	int counter = 0;
	int min = 32;

	int startingPOS = 0;
	int startCounter = 0;

	current = head;

	while(current->next != NULL) {

		//Checks the current spot to see if the program being added is already a program
		if (current->data == inserted) {
			cout << "That program already exists." << endl;
			return false;		
		}

		//If a spot contains free it starts the placement counter
		if (current->data == "Free") {
			//If a spot has free the counter of spots with "free" in a row starts
			while (current->data == "Free") {
				if (current->next != NULL) {
					counter++;
					current = current->next;
					startCounter++;
				}
				else
				{
					break;
				}
			}

			//Using the if statements the counter is set equal to the min(spots open) and the best starting index is changed
			if (counter >= size) {
				
				if (counter < min) {
					min = counter;
					startingPOS = startCounter-counter;
					best = startingPOS;
				}

			}

		}

		else if (current->next != NULL) {
			current = current->next;
			startCounter++;
		}

		counter = 0;
	}

	//returns if the best fit is true(works) or false(doesn't work)
	return (min >= size && (counter>=size)) ? true : false;
}

//Method to see if a worst fit algorithm is possible
bool LinkedList::worstFit(string data, int size) {
	//Makes method variables
	int max = 0;
	//When I set counter equal to 0, the program would only populate 31 out of 32 blocks
	//For counter=2 it would populate all 32 blocks, I am not completely sure why my counting was orignally off by one.
	int counter = 1;

	current = head;
	int startingPOS = 0;
	int startCounter = 0;

	while(current->next != NULL){
		////Checks the current spot to see if the program being added is already a program
		if (current->data == data) {
			std::cout << "That program already exists.";
			return false;
		}

		//If a spot contains free it starts the placement counter
		if (current->data == "Free") {
			startingPOS = startCounter;
			//If a spot has free the counter of spots with "free" in a row starts
			while (current->data == "Free") {

				if (current->next != NULL) {
					counter++;
					current = current->next;
					startCounter++;

				}
				else {
					break;
				}


				//Using the if statement the max number of consecutive spots open is set to counter and
				//the worst starting index is set to start
				if (counter > max) {
					max = counter;
					worst = startingPOS;
				}
			}
			counter = 0;
			
		}

		else if (current->next != NULL) {
			current = current->next;
			startCounter++;
		}

	}
	//Returns if the worst fit algorithm will work or not

	return (max >= size) ? true : false;
}

//Used for adding a program in
//This method is used in a loop in the main program
void LinkedList::replace(string data, int pos) {
	current = head;

	//Gets the current node to the correct index according to the starting position in the best/worst algorithm
	for (int i = 0; i < pos; i++) {
		current = current->next;
	}
	//Sets the data in that node to the data inputed by the user
	current->data = data;

}

bool LinkedList::remove(string data) {
	current = head;

	//Bool to see if a the program of name data exists
	bool exists = false;
	pagesRemoved = 0;

	for (int i = 0; i < 32; i++) {
		//Sees if any node has data matching the input
		//If it does that program is removed and the page increments 
		if (current->data == data) {
			current->data = "Free";
			exists = true;
			pagesRemoved++;
		}

		//If not nothing happens and the next node is looked at
		if (current->next != NULL) {
			current = current->next;
		}
		
	}

	//If a node gets "deleted" it returns true
	if (exists) {
		return exists;
	}
	//If the data in the node does not match the input then it is false and 
	//a error message comes out in the main c++ file
	else {
		return exists;
	}

}

void LinkedList::printFrag() {
	current = head;
	string name;
	int counter = 0;

	//Searches for dicontinuties between programs
	for (int i = 0; i < 32; i++) {
		//If the node is free, it sets the "looked for" name to free
		//The counter is then incremented to show that the data went from free to something else, or vice versa
		if (current->data == "Free" && name != "Free") {
			name = "Free";
			counter++;
		}
		else if (current->data != name) {
			name = current->data;
		}
		else if (current->next != NULL) {
			current = current->next;
		}
	}
	std::cout << "Number of fragments: " << counter << endl;
}

//Prints the Linked List
void LinkedList::printLL() {
	current = head;
	string temp = "";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			if (current->data == "Free") {
				cout << current->data;
			}
			else {
				cout << "  " << current->data;
			}
			current = current->next;
			cout << " ";
		}
		cout << endl;
	}

}
