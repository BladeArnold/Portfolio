
/*
Student Name: Blade Arnold
Student NetID: baa215
Compiler Used: <Visual Studio>
Program Description: This program makes two bst trees and does differnt operations on the trees and can load and save files.
*/




#include "BST.h"
#include "Node.h"
#include <fstream>

using namespace std;

void load(string file, string prompt, BST<Node, int>& tickettree, BST<Node, string>& usertree); // load prototype 


void readdata(istream& is, string prompt, BST<Node, int>& tickettree, BST<Node, string>& usertree) // executes all the commands
{
	string txt;
	if (prompt != "")
	{
		cout << prompt;
	}
	while (getline(is, txt))
	{

		stringstream ss(txt);
		string cmd, file, bst, userid, ticketid, treeid, orderid;

		getline(ss, cmd, ' ');

		if (cmd == "load")
		{
			if (!getline(ss, file, ' '))
			{
				cout << "missing required argument 1" << endl;
				continue;
			}
			
			load(file, prompt, tickettree, usertree);
			
		}

		if (cmd == "display") // displays all the orders 
		{
			if (!getline(ss, treeid, ' '))
			{
				cout << "missing required argument 1" << endl;
				continue;
			}

			if (!getline(ss, orderid))
			{
				cout << "missing required argument 2" << endl;
				continue;
			}

			if (treeid == "ticket")
			{
				if (orderid == "in")
				{
					cout << "Ticket's In Order Traversal. " << endl;
					tickettree.inOrder(cout);
				}
				else if (orderid == "pre")
				{
					cout << "Ticket's Pre Order Traversal. " << endl;
					tickettree.preOrder(cout);
				}
				else if (orderid == "post")
				{
					cout << "Ticket's Post Order Traversal. " << endl;
					tickettree.postOrder(cout);
				}
				else
				{
					cout << "Invalid order. Must be in, pre, or post" << endl;
				}
			}

			else if (treeid == "user")
			{
				if (orderid == "in")
				{
					cout << "User's In Order Traversal. " << endl;
					usertree.inOrder(cout);
				}
				else if (orderid == "pre")
				{
					cout << "User's Pre Order Traversal. " << endl;
					usertree.preOrder(cout);
				}
				else if (orderid == "post")
				{
					cout << "User's Post Order Traversal. " << endl;
					usertree.postOrder(cout);
				}
				else
				{
					cout << "Invalid order. Must be in, pre, or post" << endl;
				}
			}

			else
			{
				cout << "Invalid tree. Must be ticket or user." << endl;
			}


		}

		if (cmd == "new") // makes new trees
		{
			tickettree.destroy();
			usertree.destroy();
			tickettree = BST<Node, int>();
			usertree = BST<Node, string>();
		}

		if (cmd == "remove") // removes info
		{
			if (!getline(ss, userid, ' '))
			{
				cout << "missing required argument 1" << endl;
				continue;
			}

			if (!getline(ss, ticketid))
			{
				cout << "missing required argument 2" << endl;
				continue;
			}
			int ticketint = stoi(ticketid);
			Node* tnode = new ticketNode(userid, ticketint);
			Node* unode = new userNode(userid, ticketint);
			tickettree.remove(tnode);
			usertree.remove(unode);
			cout << "Removed user " << userid << " ticket " << ticketid << endl;

		}

		if (cmd == "find") // finds info
		{
			if (!getline(ss, userid, ' '))
			{
				cout << "missing required argument 1" << endl;
				continue;
			}

			if (!getline(ss, ticketid))
			{
				cout << "missing required argument 2" << endl;
				continue;
			}
			
			if (usertree.find(userid))
			{
				cout << "User @ ticket " << userid << " @ " << ticketid << " was found." <<endl;
			}
			else
			{
				cout << "User @ ticket " << userid << " @ " << ticketid << " does not exist." << endl;
			}
		}




		if (cmd == "add") // add or inserts info
		{
			if (!getline(ss, userid, ' '))
			{
				cout << "missing required argument 1" << endl;
				continue;
			}

			if (!getline(ss, ticketid))
			{
				cout << "missing required argument 2" << endl;
				continue;
			}
			int ticketno = stoi(ticketid); 

			Node* unode = new userNode(userid, ticketno);
			Node* tnode = new ticketNode(userid, ticketno);
			tickettree.add(tnode);
			usertree.add(unode);
			cout << "Added " << userid << " @ " << ticketid << " to system." << endl;
		}



		if (cmd == "save") // saves a tree
		{
			if (!getline(ss, bst, ' '))
			{
				cout << "missing required argument 1" << endl;
				continue;
			}
			string into; 
			if (!getline(ss, into, ' '))
			{
				cout << "missing required argument 2" << endl;
				continue;
			}
			if (into != "into")
			{
				cout << "Missing key word into." << endl;
				continue;
			}

			if (!getline(ss, file))
			{
				cout << "missing required argument 3" << endl;
				continue;
			}
			if (bst == "user")
			{
				

				ofstream ofs(file, std::ofstream::out);
				if (ofs.is_open())
				{
					usertree.postOrder(ofs);
				}
				else
				{
					cout << "Unable to open file " << file << endl;
				}
				ofs.close();
			}
			else if (bst == "ticket")
			{
				ofstream ofs(file, std::ofstream::out);
				if (ofs.is_open())
				{
					tickettree.postOrder(ofs);
				}
				else
				{
					cout << "Unable to open file " << file << endl;
				}
				ofs.close();
			}
			else
			{
				cout << "Must save either user or ticket tree. " << endl;
			}
		}

		if (cmd == "exit" || cmd == "quit") // exits the program
		{
			exit(0);
		}

		if (prompt != "")
		{
			cout << prompt;
		}
	}
}

void load(string file, string prompt, BST<Node, int>& tickettree, BST<Node, string>& usertree) // load function
{

	ifstream ifs(file);

	if (ifs.is_open())
	{
		readdata(ifs, prompt, tickettree, usertree);
	}

	else
	{
		cout << "Unable to open the file " << file << endl;
	}

	ifs.close();
}


int main() // executes code
{
	BST <Node, string> usertree;
	BST <Node, int> tickettree;
	readdata(cin, ">> ", tickettree, usertree);
}
		