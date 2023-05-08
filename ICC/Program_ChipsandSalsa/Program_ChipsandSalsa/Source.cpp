// Jason Woodward        Blade Arnold
//November 20, 2019      Fall 2019
// CSC 2134              A Period

// A report that displays the total number sold for each salsa type,
//total number of ars sold for all salsa types, and the highest selling
//product and the lowest selling product

#include <iostream>
using namespace std;

int main()
{
	const int salsa = 5;
	string name[salsa];
	int salsa_jar[salsa];
	int total = 0;

		for (int s = 0; s < salsa; s++)
		{
			cout << "Please enter the salsa name." << endl;
			cin >> name[s];

			cout << "Please enter the number of jars." << endl;
			cin >> salsa_jar[s];
		}

		int highest = salsa_jar[0];
		for (int s = 0; s < salsa; s++)
		{
			if (salsa_jar[s] > highest)
				highest = salsa_jar[s]; 
		}

		int lowest = salsa_jar[0];
		for (int s = 0; s < salsa; s++)
		{
			if (salsa_jar[s] < lowest)
				lowest = salsa_jar[s];
		}

		for (int sum : salsa_jar)
		{
			total += sum;
		}
		
		cout << "First salsa: " << name[0] << " " << salsa_jar[0] << endl;
		cout << "Second Salsa: " << name[1] << " " << salsa_jar[1] << endl;
		cout << "Third Salsa: " << name[2]<< " " << salsa_jar[2] << endl;
		cout << "Fourth Salsa: " << name[3] << " " << salsa_jar[3] << endl;
		cout << "Fifth Salsa: " << name[4] << " " << salsa_jar[4] << endl;
		cout << "Highest: " << highest << endl;
		cout << "Lowest: " << lowest << endl;
		cout << "Total: " << total << endl;

		system("PAUSE");
		return 0;
}