//Jason Woodward        Blade Arnold
//September 11, 2019    Fall 2019
//CSC 2134              A Period

//This program will ask the user to enter a month, day and two digit year. 
//the program should then detemine whether the month times the day is
//equal to the year. if so it should display magic.

#include <iostream>
using namespace std;

int main()
{
	int month;
	cout << "What is the numeric form of the month? " << endl;
	cin >> month;

	int day;
	cout << "What is the numeric form of the day? " << endl;
	cin >> day;

	int year;
	cout << "What is the last two digits of the year? " << endl;
	cin >> year;

	int total = day * month;
	cout << total << endl;

	if (total == year)
	{
		cout << "Magic Date " << endl;
	}
	if (total != year)
	{
		cout << "Not Magic Date " << endl;
	}
	system("PAUSE");

	return 0;
}

