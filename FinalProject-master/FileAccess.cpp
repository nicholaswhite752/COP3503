/* 
 * File: FileAccess.cpp
 * Author: Logan Hughes
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "FileAccess.h"
#include "sha256.h"
#include "itemStruct.h"
#include "profileStruct.h"

using namespace std;



//Checks login.csv file
//If login.csv exists, true is returned, otherwise false is returned
//If login.csv does not exist, it is created with a default admin account
bool loginExists(){ 
    ofstream loginFileOut;
    ifstream loginFileIn;
    loginFileIn.open("login.csv");    
    if (!loginFileIn.good()){
        loginFileOut.open("login.csv");
        loginFileOut << "admin,a," << sha256("password");
        loginFileOut.close();
        loginFileIn.close();
        return false;
    }
    else {
        loginFileIn.close();
        return true;
    }
}
//Checks inventory.csv file
//If inventory.csv exists, true is returned, otherwise false is returned
//If inventory.csv does not exist, it is created
bool inventoryExists(){
    ofstream inventoryFileOut;
    ifstream inventoryFileIn;
    inventoryFileIn.open("inventory.csv");    
    if (!inventoryFileIn.good()){
        inventoryFileOut.open("inventory.csv");
        inventoryFileOut.close();
        inventoryFileIn.close();
        return false;
    }
    else {
        inventoryFileIn.close();
        return true;
    }
}

/*
 * Authorizes login attempt based on passed username and password
 * Returns character corresponding to given position ('a' for admin, etc.)
 * Returns 'U' for unfound username and 'P' for bad password
 * Will create a new login file if none is found with default credentials
 * Username is not case sensitive, password is
*/
char authorize(string name, string password){
    string nameTest = name;
    transform(nameTest.begin(), nameTest.end(), nameTest.begin(), ::tolower);
    string passwordTest = sha256(password);
    loginExists();
    bool notFoundAccount = true;
    ifstream loginFileIn;
    loginFileIn.open("login.csv");
    string accountLine;
    char letter;
    string checkName, checkPass;
    while (getline(loginFileIn, accountLine) && notFoundAccount){
        istringstream accountLineStream(accountLine);
        string tempWord;
        getline(accountLineStream, tempWord, ',');
        checkName = tempWord;
        getline(accountLineStream, tempWord, ',');
        letter = tempWord.at(0);
        getline(accountLineStream, tempWord, ',');
        checkPass = tempWord;
        if (name.compare(checkName) == 0){
            notFoundAccount = false;
            if (sha256(password).compare(checkPass) == 0){
                loginFileIn.close();
                return letter;
            }
            else{
                loginFileIn.close();
                return 'P';
            }
        }
    }
    loginFileIn.close();
    return 'U';
}
vector<profile> getProfileVector(){
    vector<profile> myAccounts;
    loginExists();
    ifstream profileFileIn;
    profileFileIn.open("login.csv");
    string intake;
    string myUser, myPass;
    char myLevel;
    while (getline(profileFileIn, intake)){
        istringstream myCurrentLine(intake);
        string tempWord;
        getline(myCurrentLine, tempWord, ',');
        myUser = tempWord;
        getline(myCurrentLine, tempWord, ',');
        myLevel = tempWord.at(0);
        getline(myCurrentLine, tempWord, ',');
        myPass = tempWord;
        profile toAdd;
        toAdd.level = myLevel;
        toAdd.password = myPass;
        toAdd.user = myUser;
        myAccounts.push_back(toAdd);        
    }
    profileFileIn.close();
    return myAccounts;
}
//Returns a vector of all items in inventory file
//Order is Item Number, Item Name, Price, Quantity
vector<item> getItemVector(){
    vector<item> myInventory;
    inventoryExists();
    ifstream inventoryFileIn;
    inventoryFileIn.open("inventory.csv");
    string intake;
    int myItemNumber, myQuantity;
    double myPrice;
    string myItemName, myDescription;
    while (getline(inventoryFileIn, intake)){
        istringstream myCurrentLine(intake);
        string tempWord;
        getline(myCurrentLine, tempWord, ',');
        stringstream toConvertIN(tempWord);
        toConvertIN >> myItemNumber;
        getline(myCurrentLine, tempWord, ',');
        myItemName = tempWord;
        getline(myCurrentLine, tempWord, ',');
        myDescription = tempWord;
        getline(myCurrentLine, tempWord, ',');
        stringstream toConvertP(tempWord);
        toConvertP >> myPrice;
        getline(myCurrentLine, tempWord, ',');
        stringstream toConvertQ(tempWord);
        toConvertQ >> myQuantity;
        item toAdd;
        toAdd.itemNumber = myItemNumber;
        toAdd.itemName = myItemName;
        toAdd.description = myDescription;
        toAdd.price = myPrice;
        toAdd.quantity = myQuantity;
        myInventory.push_back(toAdd);
    }
    inventoryFileIn.close();
    return myInventory;
}
//Overwrites inventory file with new item vector
void writeInventory(vector<item> myInventory){
    inventoryExists();
    ofstream inventoryFileOut;
    inventoryFileOut.open("inventory.csv");
    clearInventory();
    for (int i = 0; i < myInventory.size(); i++){
        inventoryFileOut << myInventory[i].itemNumber << "," << myInventory[i].itemName << "," << myInventory[i].description << "," << myInventory[i].price << "," << myInventory[i].quantity;
        if (i != 1){
            inventoryFileOut << "\n";
        }
    }
    inventoryFileOut.close();
}
//Overwrites login file with new profile vector
void writeProfile(vector<profile> myAccounts){
    loginExists();
    ofstream loginFileOut;
    loginFileOut.open("login.csv");
    clearLogin();
    for (int i = 0; i < myAccounts.size(); i++){
        loginFileOut << myAccounts[i].user << "," << myAccounts[i].level << "," << myAccounts[i].password;
        if (i != 1){
            loginFileOut << "\n";
        }
    }
    loginFileOut.close();
}
/*
 * This method will add a new account to the login csv
 * If the username exists already and replace is false, the method returns false
 * If the username exists already and replace is true, the method will replace that profile item with the new information
*/
bool addProfile(char newLevel, string newUser, string newPass, bool replace){
    profile toAdd;
    toAdd.level = newLevel;
    toAdd.user = newUser;
    toAdd.password = sha256(newPass);
    vector<profile> myAccounts = getProfileVector();
    for (int i = 0; i < myAccounts.size(); i++){
        if (toAdd.user.compare(myAccounts[i].user) == 0)
            if (replace){
                myAccounts[i] = toAdd;
                writeProfile(myAccounts);
                return true;
            }
            else{
                return false;
            }
    }
    myAccounts.push_back(toAdd);
    writeProfile(myAccounts);
    return true;
}
//This method will delete the relevant user from the login file
//If username cannot be found, it returns false, returning true if deletion is successful
bool deleteProfile(string userSearch){
    vector<profile> myAccounts = getProfileVector();
    for (int i = 0; i < myAccounts.size(); i++){
        if (userSearch.compare(myAccounts[i].user) == 0){
            myAccounts.erase(myAccounts.begin() + i);
            writeProfile(myAccounts);
            return true;
        }
    }
    return false;
}
//Clear the contents of their respective csv files;
void clearLogin(){
    ofstream clear;
    clear.open("login.csv", ios::trunc);
    clear.close();
}
void clearInventory(){
    ofstream clear;
    clear.open("inventory.csv", ios::trunc);
    clear.close();
}
