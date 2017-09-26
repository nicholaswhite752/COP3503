#include "Inventory.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>

// vector of structs
// think about just doing things by number

using namespace std;

Menu::Menu(){
	temp = Inventory();
}

bool Menu::loginExist(user){
	vector<user>::iterator position;
	position = find(loginList.begin(), loginList.end());
	if(position != loginList.end()){
		return true;
	}
	else{
		return false;
	}
}

int Menu::checkLogin(user){
	//bool b = false;
	// Loop through the vector, search for the username and password combination
	return 0;
}

void Menu::createAccount(){
	// Should ask for account information and then check if it exists before
	// pushing it into the vector of accounts
	string username;
	string password;
	string position;
	cout << "Please enter a username:" << endl;
	cin >> username;
	cout << "Please enter a password:" << endl;
	cin >> password;
	cout << "Please enter a position:" << endl;
	cin >> position;
	user temp;
	temp.username = username;
	temp.password = password;
	temp.position = position;
	if(!loginExist(temp)){
		loginList.push_back(temp);
	}
	else{
		cout << "Account already exists" << endl;
	}

}

void Menu::loginMenu(){
	string username;
	string password;
	cout << "Please enter your username:" << endl;
	cin >> username;
	cout << "Please enter your password:" << endl;
	cin >> password;
	// checkLogin(username, password);
	// this will check to see if the user is actually a user and what position they are

}

void Menu::printInventory(){
	temp.printInventory();
}

void Menu::initializeInventory(){
	temp.populateInventory();
	temp.printInventory();
}

void Menu::addItem(){

	string name;
	int itemNumber;
	double price;
	int quantity;
	cout << "Please enter the name of the item:" << endl;
	//getline(cin, name);
	cin >> name;
	cout << "Please enter the item number:" << endl;
	cin >> itemNumber;
	cout << "Pleae enter the price of the item:" << endl;
	cin >> price;
	cout << "Please enter the quantity of the item" << endl;
	cin >> quantity;
	if (quantity < 0 && itemNumber < 0 && price < 0){
		cout << "Invalid quantity." << endl;
	}
	else{
		temp.createItem(name, itemNumber, price, quantity);
		cout << endl;
		cout << "Successfully added " << name << " to stock" << endl;
		cout << endl;
	}
}

void Menu::deleteItem(){
	int input;
	string name;
	int itemNumber;
	cout << "Delete by name or by item number?" << endl;
	cout << "1. Name" << endl;
	cout << "2. Item Number" << endl;
	cin >> input;
	if (input == 1){
		cout << "Please input the name of the item:" << endl;
		getline(cin, name);
		temp.deleteItemByName(name);
		cout << endl;
		cout << "Successfully deleted " << name <<  " from stock" << endl;
		cout << endl;
	}
	else if(input == 2){
		cout << "Please input the item number:" << endl;
		cin >> itemNumber;
		temp.deleteItemByItemNumber(itemNumber);
		cout << endl;
		cout << "Successfully deleted item " << itemNumber << " from stock" << endl;
		cout << endl;
	}
	else {
		cout << "Invalid input" << endl;
	}
}

void Menu::updateQuantity(){
	int input;
	string name;
	int itemNumber;
	int newQuantity;
	cout << "Update qunatity by name or by item number?" << endl;
	cout << "1. Name" << endl;
	cout << "2. Item Number" << endl;
	cin >> input;
	if (input == 1){
		cout << "Please input the name of the item:" << endl;
		// TODO: FIX THIS BECAUSE IT THINKS NOTHING EXISTS IT'S DUMB
		// cin >> name;
		// cin.ignore();
		getline(cin, name);
		cout << "Please enter the new quantity:" << endl;
		cin >> newQuantity;
		temp.updateQuantityByName(name, newQuantity);
		cout << endl;
		cout << "Successfully changed quantity to: " << newQuantity << endl;
		cout << endl;
	}
	else if(input == 2){
		cout << "Please input the item number:" << endl;
		cin >> itemNumber;
		cout << "Please enter the new quantity:" << endl;
		cin >> newQuantity;
		temp.updateQuantityByItemNumber(itemNumber, newQuantity);
		cout << endl;
		cout << "Successfully changed quantity to: " << newQuantity << endl;
		cout << endl;
	}
	else{
		cout << "Invalid input" << endl;
	}

}

void Menu::updatePrice(){
	double newPrice;
	string name;
	cout << "Pleaes enter the name of the item: " << endl;
	cin >> name;
	cout << "Please enter the new price: " << endl;
	cin >> newPrice;
	temp.updatePriceByName(name, newPrice);
	cout << "Successfully changed the price of " << name << " to $" << newPrice << endl;
}

void Menu::adminMenu(){
	bool b = true;
	int input;
	initializeInventory();
	cout << "Please select an option from the Menu: " << endl;
	while (b){

		cout << "1. Add an item to stock" << endl;
		cout << "2. Remove an item from stock" << endl;
		cout << "3. Change quantity of an item in stock" << endl;
		cout << "4. Change price of an item in stock" << endl;
		cout << "5. Print current inventory" << endl;
		cout << "6. Add an account" << endl;
		cout << "7. Delete an account" << endl;
		cout << "8. Update account information" << endl;
		cout << "9. Exit" << endl;
		cin >> input;
		switch(input){

			case 1:
			addItem();
			break;

			case 2:
			deleteItem();
			// do
			break;

			case 3:
			updateQuantity();
			break;

			case 4:
			// change price
			break;

			case 5:
			cout << endl;
			printInventory();
			cout << endl;
			break;

			case 6:
			break;

			case 7:
			break;

			case 8:
			break;

			case 9:
			b = false;
			break;

			default:
			cout << "\nPlease enter a valid option from the Menu\n" << endl;
			break;
		}
	}
}

void Menu::managerMenu(){
	bool b = true;
	int input;
	initializeInventory();
	cout << "Please select an option from the Menu: " << endl;
	while (b){

		cout << "1. Add an item to stock" << endl;
		cout << "2. Remove an item from stock" << endl;
		cout << "3. Change quantity of an item in stock" << endl;
		cout << "4. Change price of an item in stock" << endl;
		cout << "5. Print current inventory" << endl;
		cout << "6. Exit" << endl;
		cin >> input;
		switch(input){

			case 1:
			addItem();
			break;

			case 2:
			deleteItem();
			// do
			break;

			case 3:
			updateQuantity();
			break;

			case 4:
			updatePrice();
			break;

			case 5:
			cout << endl;
			printInventory();
			cout << endl;
			break;

			case 6:
			b = false;
			break;

			default:
			cout << "\nPlease enter a valid option from the Menu\n" << endl;
			break;
		}
	}
}

// Edit part about quantity
void Menu::cashierMenu(){
	bool b = true;
	int input;
	initializeInventory();
	cout << "Please select an option from the Menu: " << endl;
	while (b){
		//cout << "Please select an option from the Menu: " << endl;
		cout << "1. Change quantity of an item in stock" << endl;
		cout << "2. Print current inventory" << endl;
		cout << "3. Exit" << endl;
		cin >> input;
		switch(input){

			case 1:
			// Decrease quantity;
			break;

			case 2:
			cout << endl;
			printInventory();
			cout << endl;
			break;

			case 3:
			b = false;
			break;

			default:
			cout << "\nPlease enter a valid option from the Menu\n" << endl;
			break;
		}
	}
}

// Edit part about quantity
void Menu::stockerMenu(){
	bool b = true;
	int input;
	initializeInventory();
	cout << "Please select an option from the Menu: " << endl;
	while (b){

		cout << "1. Increaes quantity of an item in stock" << endl;
		cout << "2. Decrease quantity of an item in stock" << endl;
		cout << "3. Print current inventory" << endl;
		cout << "4. Exit" << endl;
		cin >> input;
		switch(input){

			case 1:
			// increase quantity
			break;

			case 2:
			// decrease quantity
			break;

			case 3:
			cout << endl;
			printInventory();
			cout << endl;
			break;

			case 4:
			b = false;
			break;

			default:
			cout << "\nPlease enter a valid option from the Menu\n" << endl;
			break;
		}
	}
}
