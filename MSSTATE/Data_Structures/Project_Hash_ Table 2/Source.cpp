#include<iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <string>
#include <sstream>
#include "Hashtable.h"

/*
Student Name: Blade Arnold
Student NetID: baa215
Compiler Used: Visual Studio
Program Description:
This program uses a heap to collect task and use priority to run through the task and complete them with steps.
*/
using namespace std;



class Hash
{
private:
	Hashtable table;


public:


	void readpwd(string filename)
	{
		ifstream in(filename, ifstream::in);
		table.readpwd(in);
		in.close();
	}
	void savepwd(string filename)
	{
		ofstream out(filename, ofstream::out);
		table.savepwd(out);
		out.close();
	}


	void readdata(istream& is, string prompt) // executes all the commands
	{
		string txt;
		while (getline(is, txt))
		{
			if (prompt != "")
			{
				cout << prompt << " ";
			}

			stringstream ss(txt);
			string cmd, file;

			getline(ss, cmd, ' ');

			if (cmd == "load")
			{
				string tmp;

				if (!getline(ss, file, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				if (!getline(ss, tmp))
				{
					cout << "Loading and executing script from file" << endl << endl;
					load(file, prompt);
					continue;
				}
				string pwd = file;
				file = tmp;
				cout << "Read users from file" << endl << endl;
				readpwd(file);

			}

			if (cmd == "save")
			{
				string pwd;

				if (!getline(ss, pwd, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				if (!getline(ss, file))
				{
					cout << "missing required argument 2" << endl;
					continue;
				}
				cout << "Saving users to file." << endl << endl;
				savepwd(file);
			}

			if (cmd == "new")
			{
				string userid, pwd;
				if (!getline(ss, userid, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				if (!getline(ss, pwd, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				bool isadded = table.add(userid, pwd);
				if (isadded)
				{
					cout << "Succcessfully added user." << endl;
				}
				else
				{
					cout << "Failed to add user." << endl;
				}
				
			}

			if (cmd == "remove")
			{
				string userid;
				if (!getline(ss, userid, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				bool isremoved = table.remove(userid);
				if (isremoved) 
				{
					cout << "Removed user." << endl;
				}
				else
				{
					cout << "Failed remove user." << endl;
				}
				
			}

			if (cmd == "clear")
			{
				table.clear();
				cout << "Table has been cleared." << endl;
			}


			if (cmd == "display")
			{
				string userid;
				if (!getline(ss, userid, ' '))
				{
					cout << endl;
					cout << "Displaying the user table" << endl;
					cout << table << endl;
					continue;
				}
				table.printuser(userid);
				//cout << table << endl;

			}



			if (cmd == "verify")
			{
				string userid, pwd;
				if (!getline(ss, userid, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				if (!getline(ss, pwd, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				bool isverified = table.verify(userid, pwd);
				if (isverified) 
				{
					cout << "User succcessfully validated." << endl;
				}
				else
				{
					cout << "Verication has failed." << endl;
				}
			}


			if (cmd == "home")
			{
				string userid, home;
				if (!getline(ss, userid, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				if (!getline(ss, home, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				table.changehome(userid, home);
				cout << "Succcessfully changed the home directory." << endl;
			}

			if (cmd == "passwd")
			{
				string userid, pwd;
				if (!getline(ss, userid, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				if (!getline(ss, pwd, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				table.changepwd(userid, pwd);
				cout << "Succcessfully changed the password." << endl;

			}


			if (cmd == "exit" || cmd == "quit")  // exits the program
			{
				exit(0);
			}


		}
	}









	void load(string file, string prompt) // load function
	{

		ifstream ifs(file);

		if (ifs.is_open())
		{
			readdata(ifs, prompt);
		}

		else
		{
			cout << "Unable to open the file " << file << endl;
		}

		ifs.close();
	}

};

int main()
{
	Hash hash; 
	hash.readdata(cin, ">>");

}