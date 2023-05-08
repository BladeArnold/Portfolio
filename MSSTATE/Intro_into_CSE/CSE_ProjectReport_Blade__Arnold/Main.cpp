#include <iostream>
#include <string>

using namespace std;

int answer5; // for the survey input
string question;// the question you type
string answer1, answer2, answer3, answer4, yes;// your answers
string getquestion();// gets the question
string getanswers();// gets the answer



int main()
{
	int choice; // users choice
	int condition = 1;// keeps the while loop going

	cout << "Hello, welcome to a survey maker." << endl;

	

	while (1)
	{
		cout << endl;
		cout << "1. Create survey." << endl;
		cout << "2. Create Answers." << endl;
		cout << "3. Display Survey." << endl;
		cout << "4. Run survey." << endl;
		cout << "5. Exit." << endl << endl;
		cin >> choice; // user input

			if (choice == 1)// gets the users survey question
			{
				
				cout << "You chose to create a survey." << endl;
				cout << "Please input your survey question." << endl;
				cin.ignore();
				getline(cin, question);
				cout << "You have made your question." << endl;
					
				
	
			}

			else if (choice == 2)// gets the users survey answers
			{
				
				cout << "You chose to create up to three answers." << endl;
				cout << "What would you like your first answer to be about." << endl;
				cin.ignore();
				getline(cin, answer1);// user input
				cout << "Would you like to add another answer? (yes / no)" << endl;
				cin >> answer4;// user input
				if (answer4 == "yes")
				{
					cout << "What would you like your second answer to be about." << endl;
					cin.ignore();
					getline(cin, answer2);// user input
					cout << "Would you like to add another answer? (yes / no)" << endl;
					cin >> answer4;// user input
					if (answer4 == "yes")
					{
						cout << "What would you like your third answer to be about." << endl;
						cin.ignore();
						getline(cin, answer3);// user input
					}
					else
					{
						cout << "You have finsihed your answers." << endl;
					}
				}
				else
				{
					cout << "You have finsihed your answers." << endl;
				}

			}
			else if (choice == 3) // displays the users made survey
			{
				getquestion();
				getanswers();
				cout << endl << question << endl << endl;
				cout << "1. " << answer1 << endl;
				cout << "2. " << answer2 << endl;
				cout << "3. " << answer3 << endl;
			}
			else if (choice == 4)// runs and executes the survey and collect user feedback
			{
				getquestion();
				getanswers();
				int size;
				int count1 = 0;
				int count2 = 0;
				int count3 = 0;
				cout << "How many people are you surveying?" << endl;
				cin >> size;// user input
				cout << "Ok. Starting survey." << endl << endl;
				for (int i = 0; i < size; i++)
				{
					cout << question << endl;
					cout << "1. " << answer1 << endl;
					cout << "2. " << answer2 << endl;
					cout << "3. " << answer3 << endl << endl;
					cout << "Please input your answer." << endl;
					cin >> answer5;// user input
					if (answer5 == 1)
					{
						count1++;
					}
					if (answer5 == 2)
					{
						count2++;
					}
					if (answer5 == 3)
					{
						count3++;
					}
					if (answer5 >= 4)
					{
						cout << "Please enter the correct number." << endl;
						i--;
					}
					
				}
				cout << "You have finished here are your results." << endl;
				cout << "For " << answer1 << " you had " << count1 << " people answer this."<< endl;
				cout << "For " << answer2 << " you had " << count2 << " people answer this." << endl;
				cout << "For " << answer3 << " you had " << count3 << " people answer this." << endl;
			}

			else if (choice == 5) // exits the program
			{
				cout << "You have exited the program." << endl;
				system("PAUSE");
				break;
			}
	}
}

string getquestion()// code for get question
{
	return question;
}
string getanswers()// code for get answers
{
	return answer1, answer2, answer3, answer4, yes;
}