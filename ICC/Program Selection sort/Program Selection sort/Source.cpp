//Blade Arnold
//January 15, 2020		Dn1
// CSC 2144
// This program uses the selection sort algorithm to sort an array of
// integers in ascending order.

#include <iostream>
using namespace std;

//Function prototypes
void selectionSort(int [], int);
void showArray(const int[], int);

int main()
{
	const int SIZE = 6; // size of array

	// Array of unsorted Values
		int values[SIZE] = { 6, 5, 4, 3, 2, 1, };
		cout << "The Selection sort information: " << endl;

	//Displays the values
		cout << "The unsorted values are\n";
		showArray(values, SIZE);

	// Sort the array
		selectionSort(values, SIZE);

	// Display the vaules again
		cout << "The sorted values are\n";
		showArray(values, SIZE);

		system("PAUSE");
		return 0;
}

void selectionSort(int array[], int size) // the sorting process
{
	int startScan, minIndex, minValue; // the starting value, index, and scan
	int pass = 0; // number of passes
	int comp = 0; // number of comparisons
	int swap = 0; // number of swaps

	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		pass++;
		minIndex = startScan;
		minValue = array[startScan];
		for (int index = startScan + 1; index < size; index++)
		{
			comp++;
			if (array[index] < minValue)
			{
				minValue = array[index];
				minIndex = index; 
			}
		}
		swap++;
		array[minIndex] = array[startScan];
		array[startScan] = minValue; 
	}
	cout << "Selection sort: " << endl;
	cout << "# of passes: " << pass << endl;
	cout << "# of comparison: " << comp << endl;
	cout << "# of swaps: " << swap << endl;
}

void showArray(const int array[], int size) // shows the array
{
	for (int count = 0; count < size; count++)
		cout << array[count] << " " << endl;
}
