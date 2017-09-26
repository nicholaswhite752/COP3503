#include <iostream>
#include "Inventory.h"
#include <string>
#include <vector>

using namespace std;

#ifndef Menu_H_
#define Menu_H_

struct user {
	string username;
	string password;
	string position;
};

class Menu{
private:
	// vector to hold all of the user information
	vector<user> loginList;

public:
	Menu();
	void createAccount();
	int checkLogin(user);
	void loginMenu();
	void adminMenu();
	void managerMenu();
	void cashierMenu();
	void stockerMenu();
	void addItem();
	void deleteItem();
	void initializeInventory();
	Inventory temp;
	void printInventory();
	void updateQuantity();
	void updatePrice();
};
#endif
