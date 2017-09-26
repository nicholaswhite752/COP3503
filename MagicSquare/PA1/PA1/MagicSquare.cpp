#include <iostream>
#include <string>
#include "MagicSquare.h"
#include "stdio.h"
using namespace std;

//Method for getting the sum in every row
void sumOfRows(int *ary[], int squareSize) {
	std::cout << "Checking the sums of every row: ";

		
	//Uses a loop to parse through each row and print out the sum all in one line
	for (int i = 0; i < squareSize; ++i) {
		//Resets the sum for each row
		int sum = 0;
		for (int j = 0; j < squareSize; ++j) {
			sum += ary[i][j];
		}
		//Prints out the sum per row
		std::cout << sum << " ";
	}

	std::cout << endl;
}

////Method for getting the sum in every column
void sumOfColumns(int *ary[], int squareSize) {
	std::cout << "Checking the sums of every column: ";

	//Uses a loop to parse each column and print out the sum
	for (int i = 0; i < squareSize; ++i) {
		//Resets column sum to 0, for each colummn
		int sum = 0;
		for (int j = 0; j < squareSize; ++j) {
			sum += ary[j][i];
		}
		//Prints out each column sum
		std::cout << sum << " ";

	}

	std::cout << endl;
}

//Method for finding the sum of the diagonals
void sumOfDiagonals(int *ary[], int squareSize) {
	std::cout << "Checking the sums of the Diagonals: ";

	//Makes a loop for diagonal going from upper right to lower left corner
	//The commented out section caused an error in -Wall for a unused value
	int upperDiagSum = 0;
	for (int i = 0, j = 0; /*i < squareSize,*/ j < squareSize; i++, j++) {
		upperDiagSum += ary[i][j];
	}
	std::cout << upperDiagSum << " ";

	//Loop for sum of lower left to upper right corner
	//The commented out section caused an error in -Wall for a unused value
	int lowerDiagSum = 0;
	for (int i = squareSize - 1, j = 0; /*i >= 0,*/ j < squareSize; --i, ++j) {
		lowerDiagSum += ary[i][j];
	}
	std::cout << lowerDiagSum << " ";

	std::cout << endl;
}


//Generates the first Magic Square
void produceSquareOne(int squareSize) {
	//Takes the squareSize to find the highest number of the counter
	int maxNum = 0;
	maxNum = squareSize * squareSize;


	//Intializes a pointer array for dynamic memory allocation
	int **ary = new int*[squareSize];
	for (int i = 0; i < squareSize; ++i) {
		ary[i] = new int[squareSize];
	}

	//Loop for set all values in array to 0
	for (int row = 0; row < squareSize; ++row)
	{
		for (int column = 0; column < squareSize; ++column)
		{
			ary[row][column] = 0;
		}
	}

	//Starting indexes
	int x;
	x = 0;
	int j = (squareSize / 2);
	int counter = 1;

	//loop for populating the array with the correct numbers using a siamese method
	while (counter <= maxNum) {

		ary[x][j] = counter;
		counter++;

		--x;
		++j;

		//Resets values of row when it goes out of bounds
		if (x < 0) {
			x = squareSize - 1;
		}

		//Resets values of columns when it goes out of bounds
		if (j > squareSize - 1) {
			j = 0;
		}

		//Statement to check if the spot that was icremented to above already has a non-zero number in it
		if (ary[x][j] != 0) {
			//If so the row placementis moved one column down and two rows up as per the algorithm
			j--;
			x++;
			x++;

			//The next two if statements are to correct the fringe case of moving from the upper right to 
			//lower left corner and increments the position correctly
			if (x >= squareSize) {
				x -= (squareSize);

			}
			if (j < 0) {
				j += squareSize;
			}

		}


	}

	std::cout << "Magic Square #1 is: " << endl;

	//Looop for printing out the sqaure using printf
	for (int row = 0; row <= squareSize - 1; ++row)
	{
		for (int column = 0; column <= squareSize - 1; ++column)
		{
			printf("%4i", ary[row][column]);
		}
		std::cout << std::endl;
	}

	//Caling methods for the sums
	sumOfRows(ary, squareSize);
	sumOfColumns(ary, squareSize);
	sumOfDiagonals(ary, squareSize);

	std::cout << endl;

	//Deleting the arraying to free up memory
	delete[] ary;
}

//Method for generating second Magic Sqaure
void produceSqaureTwo(int squareSize) {
	//Takes the squareSize to find the highest number of the counter
	int maxNum = 0;
	maxNum = squareSize * squareSize;


	//Intializes a pointer array for dynamic memory allocation
	int **ary = new int*[squareSize];
	for (int i = 0; i < squareSize; ++i) {
		ary[i] = new int[squareSize];
	}

	//Populates array with 0
	for (int row = 0; row < squareSize; ++row)
	{
		for (int column = 0; column < squareSize; ++column)
		{
			ary[row][column] = 0;
		}
	}

	//Starting indexes
	int x;
	x = (squareSize/2);
	int j = 0;
	int counter = 1;

	//loop for populating the array with the correct numbers using a siamese method
	while (counter <= maxNum) {

		ary[x][j] = counter;
		counter++;

		--x;
		--j;

		//resets row value if it goes out of bounds of the array
		if (x < 0) {
			x = squareSize - 1;
		}

		//resets column value if out of bounds of array
		if (j < 0) {
			j = squareSize - 1;
		}

		//Checks if the position incremented to has a non-zero number
		if (ary[x][j] != 0) {
			x++;
			j++;
			j++;

			//The next two if statements are to correct the fringe case of moving from the upper left to 
			//lower right corner and increments the position correctly
			if (x >= squareSize) {
				x -= (squareSize);

			}
			if (j >=squareSize ) {
				j -= squareSize;
			}

		}


	}

	std::cout << "Magic Square #2 is: " << endl;

	//Loop for printing out square using printf
	for (int row = 0; row <= squareSize - 1; ++row)
	{
		for (int column = 0; column <= squareSize - 1; ++column)
		{
			printf("%4i", ary[row][column]);
		}
		std::cout << std::endl;
	}

	//Calls methods for the sums
	sumOfRows(ary, squareSize);
	sumOfColumns(ary, squareSize);
	sumOfDiagonals(ary, squareSize);

	std::cout << endl;

	//Deletes array to free up memory
	delete[] ary;
}

//Generates the third Magic Square
void produceSquareThree(int squareSize) {
	//Takes the squareSize to find the highest number of the counter
	int maxNum = 0;
	maxNum = squareSize * squareSize;


	//Intializes a pointer array for dynamic memory allocation
	int **ary = new int*[squareSize];
	for (int i = 0; i < squareSize; ++i) {
		ary[i] = new int[squareSize];
	}

	//Populates array with 0
	for (int row = 0; row < squareSize; ++row)
	{
		for (int column = 0; column < squareSize; ++column)
		{
			ary[row][column] = 0;
		}
	}

	//Starting indexes
	int x;
	x = (squareSize-1);
	int j = (squareSize/2);
	int counter = 1;


	//loop for populating the array with the correct numbers using a siamese method
	while (counter <= maxNum) {

		ary[x][j] = counter;
		counter++;

		++x;
		++j;

		//resets row value if out of bounds
		if (x > squareSize-1) {
			x = 0;
		}

		//resets column value if out of bounds
		if (j > squareSize-1) {
			j = 0;
		}

		//checks if the incremented position has a non-zero number
		if (ary[x][j] != 0) {
			x--;
			x--;
			j--;

			//The next two if statements are to correct the fringe case of moving from the upper left to 
			//lower right corner and increments the position correctly
			if (x < 0) {
				x += (squareSize);

			}
			if (j <0) {
				j += squareSize;
			}

		}


	}

	std::cout << "Magic Square #3 is: " << endl;

	//Loop to print out square using printf
	for (int row = 0; row <= squareSize - 1; ++row)
	{
		for (int column = 0; column <= squareSize - 1; ++column)
		{
			printf("%4i", ary[row][column]);
		}
		std::cout << std::endl;
	}

	//Calls methods for the sums
	sumOfRows(ary, squareSize);
	sumOfColumns(ary, squareSize);
	sumOfDiagonals(ary, squareSize);

	std::cout << endl;

	//deletes array to free up memory
	delete[] ary;
}









int main() {


	int squareSize;

	//Uses a loop to grab a  square size from that using between 3 and 15, and odd
	while (true) {
		double tempSize=0;		
		std::cout << "Enter the size of the magic square" << endl;
		std::cin >> tempSize;
		
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		
		//Checks for decimal input
		if (tempSize!= (int)tempSize){
			std::cout << "Do not enter decimals" << endl;
			continue;	
		}
		
		//Checks for string input
		if (tempSize==0){
			std::cout << "Invalid Input" << endl;
			continue;	
		}


		//Checks for out of range input
		if (tempSize < 3 || tempSize > 15) {
			std::cout<< "Out of range" <<endl;
			continue;
		}

		if (tempSize >= 3 && tempSize <= 15 && ((int)tempSize % 2 == 1)) {
			squareSize = tempSize;
			break;
		}

	}
	
	//Calls the methods to produce the Magic Squares using the size given by the user
	produceSquareOne(squareSize);
	produceSqaureTwo(squareSize);
	produceSquareThree(squareSize);
}



