#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include "stdio.h"

using namespace std;


//Stack class declaration
class Stack {
private:

	int stackSize;

	// Creates a node
	typedef struct node {
		string data;
		node *next;
	}*nodePtr;

	nodePtr one;
	nodePtr current;
	nodePtr temp;

//Public function declaration
public:
	Stack();
	void push(string addData);
	string top();
	string pop();
	bool contains(string data);
	int size();
	string readFile(string fileName);
	Stack getKW(string x);
	Stack getI(string x);
	Stack getC(string x);
	Stack getOPS(string x);
	Stack getDEL(string x);
	Stack getERR(string x);
};


// Constructor for the Stack object
Stack::Stack() {
	one = NULL;
	current = NULL;
	temp = NULL;
	stackSize = 0;
}

//Retrieves size of stack, used for looping
int Stack::size() {
	return stackSize;
}


string Stack::top() {
	//Sets current equal to the head or pseudo-top
	current = one;
	string result;
	bool tempCheck = false;
	while (current->next != NULL) {
		temp = current;
		current = current->next;
		if (current->data == "") {
			tempCheck = true;
			break;
		}
	}
	//Grabs either the top or current of the stack depending on the situation, and returns the data in it
	if (tempCheck) {
		result = temp->data;
		return result;

	}
	else {
		result = current->data;
		return result;
	}
	stackSize--;
	return result;
}

//Adds to the top of the stack using an inputted string
void Stack::push(string addition) {
	nodePtr n = new node;
	n->next = NULL;
	n->data = addition;
	//Makes sure the addition is possible and finds where the place to implant it is
	if (one != NULL) {
		current = one;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = n;
	}
	else {
		one = n;
	}
	//resizes
	stackSize++;
}

//Takes the data off the top of the stack and resizes
string Stack::pop() {
	//Sets the current to the first slot
	current= one;
	string result;
	//Makes sure it exsists by using a loop
	bool tempCheck = false;
	while (current->next != NULL) {
		temp = current;
		current = current->next;
		if (current->data == "") {
			tempCheck = true;
			break;
		}
	}
	//Sets the data on top or the current depending on situation equal to result, and sets it to empty
	if (tempCheck) {
		result = temp->data;
		temp->data = "";
	}
	else {
		result = current->data;
		current->data = "";
	}

	//resize and return
	stackSize--;
	return result;
}

//Used to avoid duplication
//Checks to see of the data inputted already exsists in the stack
bool Stack::contains(string addition) {
	if (stackSize != 0) {
		current = one;
		//Uses a loop to check if the inserted data is already in the target stack
		while (current->next != NULL) {
			if (current->data == addition) {
				return true;
			}
			current = current->next;
		}
		if (current->data == addition) {
			return true;
		}
		return false;
	}

	return false;
}

//Takes a filename from the user and tries to read it
string readFile(string fileName) {

	string finalFile;
	ifstream inFile;
	inFile.open(fileName.c_str());

	//Error for failure
	if (inFile.fail()) {
		cerr << "Error opening file" << endl;
	}
	//returns a string or group of strings if in a loop of the file contents
	else {
		string file;
		while (true) {
			getline(inFile, file);
			if (inFile.eof())
				break;
			finalFile += file + "\n";


		}
		//closes file
		inFile.close();
	}
	//returns contents of file
	return finalFile;

}

