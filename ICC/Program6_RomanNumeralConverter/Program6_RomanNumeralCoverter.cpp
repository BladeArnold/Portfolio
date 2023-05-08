//Jalen Garth, Destin Fox, and Blade arnld
//September 18, 2019            Fall 2019
//CSC 2134                      A Period

//This program converts numbers into Roman numerals and states if they are
//accurate or not

#include <iostream>
using namespace std;

int main()
{

	int number;

	cout << "Enter number one to ten" << endl;
	cin >> number;

	switch (number)
	{
	case 1: cout << "The Roman numeral equivalent is I" << endl;
		break;
	case 2: cout << "The Roman numeral equivalent is II" << endl;
		break;
	case 3: cout << "The Roman numeral equivalent is III" << endl;
		break;
	case 4: cout << "The Roman numeral equivalent is IV" << endl;
		break;
	case 5: cout << "The Roman numeral equivalent is V" << endl;
		break;
	case 6: cout << "The Roman numeral equivalent is VI" << endl;
		break;
	case 7: cout << "The Roman numeral equivalent is VII" << endl;
		break;
	case 8: cout << "The Roman numeral equivalent is VIII" << endl;
		break;
	case 9: cout << "The Roman numeral equivalent is IX" << endl;
		break;
	case 10: cout << "The Roman numeral equivalent is X" << endl;
		break;
	default:cout << "You did not enter number 1 through 10" << endl;
	}

	system("PAUSE"); 

	return 0;

}