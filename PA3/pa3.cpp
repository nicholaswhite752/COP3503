#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <stack>
#include "pa3.h"

using namespace std;

//Global variables used for the nested loop counter
int nestCount = 0;
int FOR = 0;
int BEGIN = 0;
//Varaible for the operators delimiter
string opsDelimiter = "";


//All the methods for distguishing the parts of the code are very similar and use very similar logic with
//slight differences

//Method for keywords
Stack getKW(string x) {

	//Vector used for splitting the original code 
	vector<string> workKW;
	//Stack that will be returned
	Stack temp;

	//Code that delimits the original code line by line by the characters specified
	//Some logic was borrrowed from an online source
	//http://stackoverflow.com/questions/7621727/split-a-string-into-words-by-multiple-delimiters-in-c
	while (true)
	{
		unsigned int prev = 0;
		unsigned int pos;
		//							Parameters that are delimited
		while ((pos = x.find_first_of(" (),;=-+/*", prev)) != std::string::npos)
		{
			if (pos > prev)
				workKW.push_back(x.substr(prev, pos - prev));
			prev = pos + 1;
		}
		if (prev < x.length())
			workKW.push_back(x.substr(prev, std::string::npos));
		break;
	}

	//Loop for testing all the words in the string vector, if they are keywords
	for (unsigned int i = 0; i < workKW.size(); i++) {
		string test = workKW[i];
		//Tests for FOR. If it matches the FOR counter increases
		if (test == "FOR") {
			temp.push("FOR");
			FOR++;
		}
		//Tests for BEGIN. If it matches the BEGIN counter increases
		else if (test == "BEGIN") {
			temp.push("BEGIN");
			BEGIN++;
		}
		//Tests for END.
		else if (test == "END") {
			temp.push("END");
			FOR--;
		}

		//The logic for how deep the nested for loops are
		if((FOR>BEGIN) && (FOR-BEGIN==1)){
			nestCount = FOR ;
		}
	}

	return temp;

}

//Method to get identifiers
Stack getI(string x) {

	//Vector for splitting the code by delimiter (explained in KW) and the return stack
	vector<string> workI;
	Stack temp;

	//Delimiting code
	while (true)
	{
		unsigned int prev = 0;
		unsigned int pos;
		//							Parameters that are delimited
		while ((pos = x.find_first_of(" (),;=-+/*", prev)) != std::string::npos)
		{
			if (pos > prev)
				workI.push_back(x.substr(prev, pos - prev));
			prev = pos + 1;
		}
		if (prev < x.length())
			workI.push_back(x.substr(prev, std::string::npos));
		break;
	}


	int tempSize = workI.size();
	//For loop that looks for identifiers (lower case)
	for (int i = 0; i < tempSize; i++) {
		string working = "";
		working += workI[i];

		//Looks at the first character of each word, if the character is lowercase then the whole word is put in the identifier stack
		//to be used later
		if (working[0] <= 'z' && working[0]>='a') {
			temp.push(working);
		}
		else {
		
		}

	}

	return temp;
}

//Method to get constants
Stack getC(string x) {

	//Vector used to delimit
	vector<string> workC;
	Stack temp;

	//Code for delimiting
	while (true)
	{
		unsigned int prev = 0;
		unsigned int pos;
		//							Parameters for the constant delimiting
		while ((pos = x.find_first_of(" (),;=-+/*FORENDBEGIN", prev)) != std::string::npos)
		{
			if (pos > prev)
				workC.push_back(x.substr(prev, pos - prev));
			prev = pos + 1;
		}
		if (prev < x.length())
			workC.push_back(x.substr(prev, std::string::npos));
		break;
	}




	int tempSize = workC.size();
	//For loop that checks each section of the code for constants
	for (int i = 0; i < tempSize; i++) {
		
		string working = "";
		working = workC[i];
		//Checks if the first character in the is a digit, if it is and the person is following proper coding conventions, then 
		//it has to be a constant
		if (isdigit(working[0])) {
			temp.push(working);
		}
		else {
		
		}
	}
	return temp;
}

//Gets the operators
Stack getOPS(string x) {
	//Vector used when splitting the original code
	vector<string> workOPS;
	Stack temp;

	//Logic for delimiting
	while (true)
	{
		unsigned int prev = 0;
		unsigned int pos;
		//							Paramter (space)
		while ((pos = x.find_first_of(opsDelimiter, prev)) != std::string::npos)
		{
			if (pos > prev)
				workOPS.push_back(x.substr(prev, pos - prev));
			prev = pos + 1;
		}
		if (prev < x.length())
			workOPS.push_back(x.substr(prev, std::string::npos));
		break;
	}

	int tempSize = workOPS.size();
	//Loop checking if a certain 
	for (int i = 0; i < tempSize; i++) {
		string working = "";
		working = workOPS[i];
		//If statements to see if a certain part of the code is an operator
		if (working[0] == '+' && working[1] == '+') {
			temp.push("++");
		}
		else if (working[0] == '-' && working[1] == '-') {
			temp.push("--");
		}
		else if (working[0] == '=') {
			temp.push("=");
		}
		else if (working[0] == '-') {
			temp.push("-");
		}
		else if (working[0] == '*') {
			temp.push("*");
		}
		else if (working[0] == '/') {
			temp.push("/");
		}
		else if (working[0] == '%') {
			temp.push("%");
		}
		else if (working[0] == '+') {
			temp.push("+");
		}
	}

	return temp;
}

//Gets delimiters (; ,)
Stack getDEL(string x) {
	//Working vector for storing delimited strings
	vector<string> workDEL;
	Stack temp;

	//Logic for delimiting
	while (true)
	{
		unsigned int prev = 0;
		unsigned int pos;
		//Parammeters
		while ((pos = x.find_first_of("() ", prev)) != std::string::npos)
		{
			if (pos > prev)
				workDEL.push_back(x.substr(prev, pos - prev));
			prev = pos + 1;
		}
		if (prev < x.length())
			workDEL.push_back(x.substr(prev, std::string::npos));
		break;
	}

	int tempSize = workDEL.size();
	//Loop for finding delimiters
	for (int i = 0; i < tempSize; i++) {
		string working = "";
		working += workDEL[i];

		//Checks the line of code if a ; or , exsists
		if (working.find_first_of(";") > 0) {
			temp.push(";");
		}
		if (working.find_first_of(",") > 0) {
			temp.push(",");
		}
	}

	return temp;
}

//Finds the Syntax errors
Stack getERR(string x) {
	//Error string vector
	vector<string> workERR;
	Stack temp;

	//Logic for delimiting
	while (true)
	{
		unsigned int prev = 0;
		unsigned int pos;
		while ((pos = x.find_first_of(" (),;=-+/*", prev)) != std::string::npos)
		{
			if (pos > prev)
				workERR.push_back(x.substr(prev, pos - prev));
			prev = pos + 1;
		}
		if (prev < x.length())
			workERR.push_back(x.substr(prev, std::string::npos));
		break;
	}

	int tempSize = workERR.size();
	//Loop for finding errors
	for (int i = 0; i < tempSize; i++) {

		string working = "";
		working = workERR[i];
		//Checks if first letter is a capital, by standard coding conventions it would be deduced that for this assignment, if it starts
		//with a capital it will be an ALL CAPS word
		if (working[0]>='A' && working[0]<='Z') {
			temp.push(working);
		}
		else {
	
		}
	}
	return temp;

	return temp;
}


int main() {
	
	string fileName;

	cout << "Please input the name of the file: " << endl;
	
	std::cin >> fileName;
  
	string temp = readFile(fileName);

	vector<string> workingLine;
	Stack KW;
	Stack CNST;
	Stack IDEN;
	Stack OPS;
	Stack DEL;
	Stack ERR;

	//Logic that delimites the very original code given straight from the file
	//Just the take out the tabs and new lines to make further deliminatnions a little easier
	while (true)
	{
		unsigned int prev = 0;
		unsigned int pos;
		//Parameters of tab and new line
		while ((pos = temp.find_first_of("\n\t", prev)) != std::string::npos)
		{
			if (pos > prev)
				workingLine.push_back(temp.substr(prev, pos - prev));
			prev = pos + 1;
		}
		if (prev < temp.length())
			workingLine.push_back(temp.substr(prev, std::string::npos));
		break;
	}
	int trueSize = workingLine.size();

	//Code for putting the key words in a stack without doubles
	for (unsigned int i = 0; i < workingLine.size(); i++) {
		//Sets a line of code to a string
		string line = workingLine[i];
		//calls the keyword method
		Stack temp = getKW(line);
		int tempC = temp.size();
		//A loop using the contains method to make sure anything on the final stack is not a duplicate
		for (int j = 0; j < tempC; j++) {
			if (!(KW.contains(temp.top()))) {
				opsDelimiter += temp.top();
				KW.push(temp.pop());
			}
		}

	}

	
	//Code for finding identifiers and placing in stacks
	for (unsigned int i = 0; i < workingLine.size(); i++) {
		string line = workingLine[i];
		//I had to use a transfer stac for this
		//I could not figure out the logic for just one stac becaues identifiers are complicated
		Stack temp = getI(line);
		Stack transfer;
		int tempI = temp.size();
		for (int j = 0; j < tempI; j++) {
			//Pushes all of the temp stack to transfer
			if (true) {
				transfer.push(temp.pop());
			}
			//Uses contain to assign to final stack without duplicates
			if ((!(IDEN.contains(transfer.top())))) {
				opsDelimiter += transfer.top();
				IDEN.push(transfer.pop());
			}
		}

	}

	//Loops for getting the constant stack
	for (int i = 0; i < trueSize; i++) {
		string line = workingLine[i];
		Stack temp = getC(line);
		int tempC = temp.size();
		//Loop for assigning the constant stack using the contains method to avoid duplicates
		for (int j = 0; j < tempC; j++) {
			if (!(CNST.contains(temp.top()))) {
				opsDelimiter += temp.top();
				CNST.push(temp.pop());
			}

		}
	}
	
	//Loop for delimiters
	for (int i = 0; i < trueSize; i++) {
		string line = workingLine[i];
		Stack temp = getDEL(line);
		int tempDEL = temp.size();
		//Uses contains to avoid duplicates
		for (int j = 0; j < tempDEL; j++) {
			if (!(DEL.contains(temp.top()))) {
				opsDelimiter += temp.top();
				DEL.push(temp.pop());
			}

		}
	}

	//Loop for Syntax Erros
	for (int i = 0; i < trueSize; i++) {
		string line = workingLine[i];
		Stack temp = getERR(line);
		int tempERR = temp.size();
		//Uses a loops to compare it to keywods to make sure a keyword is not mistaken for a syntax error
		//Then uses contains to avoid duplicates
		for (int j = 0; j < tempERR; j++) {
			if (temp.top()=="FOR" || temp.top() == "BEGIN" || temp.top() == "END"){
				
			}
			else if(!(ERR.contains(temp.top()))) {
				opsDelimiter += temp.top();
				ERR.push(temp.pop());
			}

		}
	}

	//The opsDelimter is all the other sections of code including spaces, which will only leave strings of operators
	//which are much easier to work with that picking out operators in the middle of a string
	opsDelimiter += " ";

	//Loop for assigning operators
	for (int i = 0; i < trueSize; i++) {
		string line = workingLine[i];
		Stack transfer;
		Stack temp = getOPS(line);
		int tempOPS = temp.size();
		//Uses contains to avoid duplicates

		//I once again had to use a transfer stack. I'm not completely sure on why it wouldn't recognize the "=" sign
		//on its own without the transfer stack
		for (int j = 0; j < tempOPS; j++) {
			if (temp.top()== "=" && !(OPS.contains("="))) {
				OPS.push(temp.pop());
			}
			else {
				transfer.push(temp.pop());
			}
		}

		int transC = transfer.size();
		for (int j = 0; j < transC; j++) {
			if (!(OPS.contains(transfer.top()))) {
				OPS.push(transfer.pop());
			}

		}
	}


	//Print statemnet for nested loops
	cout << "The depth of nested loop(s) is: " << nestCount << endl;

	//Printing of Key words
	int k = KW.size();
	cout << "Keywords: ";
	for (int i = 0; i < k; i++) {
		cout << KW.pop() << " ";
	}
	cout << endl;

	//Printing of identifiers
	int id = IDEN.size();
	cout << "Identifiers: ";
	for (int i = 0; i < id; i++) {
		cout << IDEN.pop() << " ";
	}
	cout << endl;

	//Printing of delimiters
	int cnst = CNST.size();
	cout << "Constants: ";
	for (int i = 0; i < cnst; i++) {
		cout << CNST.pop() << " ";
	}
	cout << endl;

	//Printing of operators
	int ops = OPS.size();
	cout << "Operators: ";
	for (int i = 0; i < ops; i++) {
		cout << OPS.pop() << " ";
	}
	cout << endl;

	//Printing of delimiters
	int del = DEL.size();
	cout << "Delimiters: ";
	for (int i = 0; i < del; i++) {
		cout << DEL.pop() << " ";
	}
	cout << endl;

	//Printing of errors
	cout << endl;
	int err = ERR.size();
	cout << "Syntax Error(s): ";
	for (int i = 0; i < err; i++) {
		cout << ERR.pop()<<" ";
	}
	cout << endl;


}


