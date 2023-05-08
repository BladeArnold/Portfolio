#include "Daily_set.h"
#include "Puzzle.h"
#include <iostream>
#include <fstream>
#include <sstream>


Daily_set::Daily_set() :numpuzzles(0)
	{

	}
	//Member Function
	void Daily_set::create(string name) // creates a puzzle
	{
		if (name == "")
		{
			return;
		}
		if (numpuzzles == 7)
		{
			cerr << "Can not have more than seven puzzles." << endl;
			return;
		}
		puzzles[numpuzzles] = Puzzle(name);
		++numpuzzles;
	}

	void Daily_set::add(string card, string name) // adds cards 
	{
		for (int i = 0; i < 7; i++)
		{
			if (puzzles[i].getName() == name)
			{
				//cout << "Line 36 " << puzzles[i].getName() << " " << name << endl;
				Card c;
				if (c.create(card))
				{
					puzzles[i].add(c);
					return;
				}
				else
				{
					return;
				}
			}
		}
		cerr << "Puzzle " << name << " does not exist." << endl;
	}
	void Daily_set::display(string name) // disaplys puzzle
	{
		if (name == "")
		{
			if (numpuzzles == 0)
			{
				cout << "There are no puzzles to display." << endl;
				return;
			}
			cout << "The following puzzles are available to edit or solve." << endl << endl;

			//print name of each puzzle
			for (int i = 0; i < numpuzzles; i++)
			{
				cout << puzzles[i].getName() << endl;
			}
			cout << endl;
			return;
		}
		else
		{
			for (int i = 0; i < numpuzzles; i++)
			{
				if (puzzles[i].getName().compare(name) == 0)
				{
					puzzles[i].display();
					return;
				}
			}
		}
		cerr << "Could not display " << name << endl;
	}

	void Daily_set::solve(string name) // solves puzzle
	{
		for (int i = 0; i < numpuzzles; i++)
		{
			if (puzzles[i].getName().compare(name) == 0)
			{
				puzzles[i].solve();
				return;
			}
		}
	}

	void Daily_set::load(string file, string puzzle)
	{
		create(puzzle);
		ifstream ifs(file);
		string card;

		if (ifs.is_open())
		{
			create(puzzle);
			while (getline(ifs, card ))
			{
			
				add(card, puzzle);

			}
			cout << "Loaded puzzle. " << endl; 
		}
	}

	void Daily_set::test(string c1, string c2, string c3)
	{
		Card card1(c1);
		Card card2(c2);
		Card card3(c3);

		if (card1.solve(card2, card3))
		{
			cout << "This cards form a set. " << endl;
		}
		else
		{
			cout << "This cards do not form a set. " << endl << endl;
		}
	}

	void Daily_set::remove(string card, string puzzle)
	{
		for (int i = 0; i < numpuzzles; i++)
		{
			//if (puzzles[i].getName().compare(puzzle) == 0)
			if (puzzles[i].getName() == puzzle)
			{
				Card c(card);
				puzzles[i].removecard(card);
				return;
			}
		}
		cout << "Unable to remove card from puzzle. " << endl;
	}
	void Daily_set::remove(string puzzle)
	{
		for (int i = 0; i < numpuzzles; i++)
		{
			//if (puzzles[i].getName().compare(puzzle) == 0)
			if (puzzles[i].getName() == puzzle)
			{
				puzzles[i] = puzzles[numpuzzles - 1];
				--numpuzzles;
				cout << "Successfully removed puzzle." << endl;
				return;
			}
		}
		cout << "Unable to remove puzzle. " << endl;
	}

	void Daily_set::readdata(istream& is, string prompt)
	{
		string txt;
		if (prompt != "")
		{
			cout << prompt;
		}
		while (getline(is, txt))
		{

			// assign the string txt to a stringstream      
			stringstream ss(txt);
			string cmd, file, puzzle, card1, card2, card3;
			// let's break this apart token by token      
			// we can handle a few command cases      
			// get the command      
			getline(ss, cmd, ' ');
			if (cmd == "load")
			{
				// has two argument  
				if (!getline(ss, file, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				puzzle = "";
				getline(ss, puzzle, ' ');

				if (puzzle == "as")
				{
					getline(ss, puzzle, ' ');
					if (puzzle == "")
					{
						cout << "Missing day" << endl;
						continue;
					}
				}
				else if (puzzle != "")
				{
					cout << "Missing as " << endl;
					continue;
				}


				load(file, puzzle);

				//cout << "Load has at least one argument and its set to " << file << "  " << puzzle << endl;
			}
			if (cmd == "display") // Dispalys the puzzle and cards in puzzle
			{
				puzzle = "";
				getline(ss, puzzle, ' ');
				display(puzzle);
				//cout << "Display has zero or one arguments. " << puzzle << endl;

			}
			if (cmd == "new") // makes a new puzzle
			{
				if (!getline(ss, puzzle, ' '))
				{
					cout << "missing required argument " << endl;
					continue;
				}
				create(puzzle);
				//cout << "new " << puzzle << endl;
			}

			if (cmd == "remove") /// removes a puzzle
			{
				// has two argument  
				if (!getline(ss, card1, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				puzzle = "";
				getline(ss, puzzle, ' ');
				if (puzzle == "from")
				{
					puzzle = "";
					getline(ss, puzzle, ' ');
					if (puzzle == "")
					{
						cout << "Missing puzzle." << endl;
						continue;
					}
					this->remove(card1, puzzle);
				}
				else if (puzzle == "")
				{
					puzzle = card1;
					card1 = "";
					this->remove(puzzle);
				}
			}

			if (cmd == "add") // adds new cards
			{
				// has two argument  
				if (!getline(ss, card1, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				getline(ss, puzzle, ' ');
				if (puzzle != "to")
				{
					cout << "missing grammer to" << endl;
					continue;
				}
				if (!getline(ss, puzzle, ' '))
				{
					cout << "missing required argument 2" << endl;
					continue;
				}

				add(card1, puzzle);
				//cout << "add " << card1 << " to " << puzzle << endl;
			}

			if (cmd == "solve") // solves a puzzle and its cards
			{
				// has two argument  
				puzzle = "";
				if (!getline(ss, card1, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				card2 = "";
				getline(ss, card2, ' ');
				if (card2 == "")
				{
					puzzle = card1;
					card2 = "";
					card1 = "";
					solve(puzzle);
					// cout << "solve " << puzzle << endl;
				}
				else
				{
					Card c2;
					c2.create(card2);
					Card c1;
					c1.create(card1);
					Card card = c1.solve(c2);
					cout << "The last card in the set is ";
					card.display();
					cout << endl;
				}


			}

			if (cmd == "test")
			{
				// has two argument  
				if (!getline(ss, card1, ' '))
				{
					cout << "missing required argument 1" << endl;
					continue;
				}
				if (!getline(ss, card2, ' '))
				{
					cout << "missing required argument 2" << endl;
					continue;
				}
				if (!getline(ss, card3, ' '))
				{
					cout << "missing required argument 3" << endl;
					continue;
				}

				this->test(card1, card2, card3);

				//cout << "Test " << card1 << "  " << card2 << "  " << card3 << endl;
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


