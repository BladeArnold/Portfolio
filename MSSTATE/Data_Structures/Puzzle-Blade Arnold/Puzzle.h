#pragma once
#include "Card.h"
#include <iostream>
#include <string>

using namespace std;

class Puzzle
{
	//Instance variables
	Card cards[12];
	int num;
	string name;

public:
	// Constructer
	Puzzle();

	Puzzle(string name);
	
	// Member Functions
	void add(Card card);
 
	string getName(); // gets name of puzzle
 

	void display(); // dispays the puzzle
 

	void solve(); // solve the cards in the puzzle
	
	void removecard(Card card);

};

