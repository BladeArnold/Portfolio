//Blade Arnold
//January 15, 2020		Dn1
// CSC 2144
// This program uses the bubble sort algorithm to sort an array of 
// integers in ascending order.

#include <iostream>
using namespace std;

//Function prototypes
void sortArray(int[], int);
void showArray(const int[], int);

int main()
{
	const int SIZE = 6; // Array size

	//Array of unsorted values 
	int values[SIZE] = { 7, 2, 3, 8, 9, 1 };

	cout << "The information below is for the Bubble Array sort." << endl;

	//Display the values 
	cout << "The unsorted values are: \n";

	showArray(values, SIZE);

	//Sort the values 
	sortArray(values, SIZE);

	//Displays the vaule
	cout << "The sorted values are: " << endl;
	showArray(values, SIZE);

	system("PAUSE");
	return 0;

}

void sortArray(int array[], int size) // sorts the array
{
	int temp;
	bool madeAswap;		// test if a swap was made
	int pass = 0;		// number of passes
	int comp = 0;		// number of comparisons
	int swap = 0;		// number of swaps

	do
	{
		pass++;
		madeAswap = false;
		for (int count = 0; count < (size - 1); count++)
		{
			comp++;
			if (array[count] > array[count + 1])
			{
				swap++;
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;
				madeAswap = true;
			}
		}
	} while (madeAswap); // Loop again if a swap occured on this pass
	
	cout << "Bubble Sort: " << endl;
	cout << "# of passes: " << pass << endl;
	cout << "# of comparisons: " << comp << endl;
	cout << "# of swaps: " << swap << endl;


}
void showArray(const int array[], int size) // shows the array
{
	for (int count = 0; count < size; count++)
		cout << array[count] << " " << endl;

}