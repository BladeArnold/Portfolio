#include "Puzzle.h"
#include "Card.h"
#include <iostream>
#include <string>

using namespace std;


	// Constructer
	Puzzle::Puzzle() :num(0)
	{
		this->name = "";
	}

	Puzzle::Puzzle(string name) :num(0)
	{
		this->name = name;
	}

	// Member Functions
	void Puzzle::add(Card card)
	{
		if (num == 12)
		{
			cerr << "No more cards can be added. Puzzle full." << endl;
			return;
		}
		cards[num] = card;
		++num;
	}
	string Puzzle::getName() // gets name of puzzle
	{
		return name;
	}

	void Puzzle::display() // dispays the puzzle
	{
		for (int i = 0; i < num; i++)
		{
			cards[i].display();

			if ((i + 1) % 4 == 0)
			{
				cout << endl << endl;
			}
		}
		cout << endl;
	}

	void Puzzle::solve() // solve the cards in the puzzle
	{
		for (int i = 0; i < num; i++)
		{
			for (int j = i + 1; j < num; j++)
			{

				for (int k = j + 1; k < num; k++)
				{

					if (cards[i].solve(cards[j], cards[k]))
					{
						cards[i].display();
						cards[j].display();
						cards[k].display();
						cout << endl << endl;
					}
				}
			}
		}
	}

	void Puzzle::removecard(Card card)
	{
		for (int i = 0; i < num; i++)
		{
			if (cards[i].equals(card))
			{
				cards[i] = cards[num - 1];
				--num;
				cout << "Successfully removed the card." << endl;
				return;
			}
		}
		cout << "Unable to remove card." << endl;
	}


