#pragma once
#include "Puzzle.h"
class Daily_set
{
	//Instance Variables
	Puzzle puzzles[7];
	int numpuzzles;

public:
	Daily_set();

	//Member Function
	void create(string name); // creates a puzzle

	void add(string card, string name); // adds cards 

	void display(string name); // disaplys puzzle


	void solve(string name); // solves puzzle

	void load(string file, string puzzle);

	void test(string c1, string c2, string c3);

	void remove(string card, string puzzle);
	
	void remove(string puzzle);

	
	void readdata(istream& is, string prompt);
	
};

