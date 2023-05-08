// Malik Small and Blade Arnold
//January 15, 2020		Dn1
// CSC 2144
// This program will find the average amount of food, the least 
// amount of food, and greatest amount of food.

#include <iostream>
using namespace std;

int main()
{
	int const ROWS = 3;			// Number of rows
	int const COLS = 7;			// Number of columns
	double monkeyFood[ROWS][COLS];  // The array 

	
	double sumOfDayOne = 0.0, averageOfDayOne = 0.0;	 // Sum and average of the day
	double sumOfDayTwo = 0.0, averageOfDayTwo = 0.0;	// Sum and average of the day
	double sumOfDayThree = 0.0, averageOfDayThree = 0.0;	// Sum and average of the day
	double sumOfDayFour = 0.0, averageOfDayFour = 0.0;	// Sum and average of the day
	double sumOfDayFive = 0.0, averageOfDayFive = 0.0;	// Sum and average of the day
	double sumOfDaySix  = 0.0, averageOfDaySix = 0.0;	// Sum and average of the day
	double sumOfDaySeven = 0.0, averageOfDaySeven = 0.0;	// Sum and average of the day

	for (int a = 0; a < ROWS; a++)
	{
		cout << "Please enter Monkey # info for " << a + 1 <<
			" , please enter the food consumed." << endl;
		for (int b = 0; b < COLS; b++)
		{
			cin >> monkeyFood[a][b];
			
		}
	}

	double smallest = monkeyFood[0][0];		// Smallest amount of food eaten
	for (int c = 0; c < ROWS; c++)
	{
		for (int d = 0; d < COLS; d++)
		{
			if (monkeyFood[c][d] < smallest)
				smallest = monkeyFood[c][d];
		}
	}

	double largest = monkeyFood[0][0];			// Largest amount of food eaten
	for (int e = 0; e < ROWS; e++)
	{
		for (int f = 0; f < COLS; f++)
		{
			if (monkeyFood[e][f] > largest)
				largest = monkeyFood[e][f];
		}
	} 

	for (int g = 0; g < ROWS; g++)
	{ 
		
		sumOfDayOne += monkeyFood[g][0];
		averageOfDayOne = sumOfDayOne / ROWS;

	}
	for (int h = 0; h < ROWS; h++)
	{
		sumOfDayTwo += monkeyFood[h][1];
		averageOfDayTwo = sumOfDayTwo / ROWS;

	}
	for (int i = 0; i < ROWS; i++)
	{
		sumOfDayThree += monkeyFood[i][2];
		averageOfDayThree = sumOfDayThree / ROWS;

	}
	for (int j = 0; j < ROWS; j++)
	{
		sumOfDayFour += monkeyFood[j][3];
		averageOfDayFour = sumOfDayFour / ROWS;

	}
	for (int k = 0; k < ROWS; k++)
	{
		sumOfDayFive += monkeyFood[k][4];
		averageOfDayFive = sumOfDayFive / ROWS;

	}
	for (int l = 0; l < ROWS; l++)
	{
		sumOfDaySix += monkeyFood[l][5];
		averageOfDaySix = sumOfDaySix / ROWS;

	}
	for (int m = 0; m < ROWS; m++)
	{
		sumOfDaySeven += monkeyFood[m][6];
		averageOfDaySeven = sumOfDaySeven / ROWS;

	}

	cout << "The average of Monday is " << averageOfDayOne << "." << endl;
	cout << "The average of Tuesday is " << averageOfDayTwo << "." << endl;
	cout << "The average of Wednesday is " << averageOfDayThree << "." << endl;
	cout << "The average of Thursday is " << averageOfDayFour << "." << endl;
	cout << "The average of Friday is " << averageOfDayFive << "." << endl;
	cout << "The average of Saturday is " << averageOfDaySix << "." << endl;
	cout << "The average of Sunday is " << averageOfDaySeven << "." << endl;
	cout << "This is the smallest amount of food eaten by a monkey this"
		" week " << smallest << "." << endl;
	cout << "This is the greatest amount of food eaten by a monkey this"
		" week " << largest << "." << endl;

	system("PAUSE");

	return 0; 
}