//Blade Arnold
//November 29, 2019		Fall 2019
//CSC 2134				A

// This program will use a class to show the dates.

#include <iostream>
using namespace std;


class date

{
	int month;
	int day;
	int year;

public:

	date(int month = 1, int day = 1, int year = 2001)

	{

		date::month = month;
		date::day = day;
		date::year = year;

	};

	void showDate();

	~date() {}

};



void date::showDate() {

	cout << month << "/" << day << "/" << year << endl;

}

int main()

{

	int month;

	int day;

	int year;


	string monthName[12] = { "January","February","March","April","May","June","July",

	"August","September","October","November","December" };



	cout << " Please enter a month between Januray and December. (Numeric form)" << endl;

	cin >> month;



	if (month > 12 || month < 1)

	{

		month = 1;

	}

	cout << "Please enter the day. (Numeric form)" << endl;

	cin >> day;


	if (day > 31 || day < 1)

	{

		day = 1;

	}

	cout << " Please enter the year. (Numeric Form)" << endl;

	cin >> year;

	if (year > 2010 || year < 1900)

	{

		year = 2001;

	}


	date newDate(month, day, year);
	newDate.showDate();
	cout << monthName[month - 1] << " " << day << ", " << year << endl;
	cout << day << " " << monthName[month - 1] << " " << year << endl;


	system("PAUSE");

	return 0;

}

