#pragma once
#include <iostream>
#include <string>

using namespace std;

class Card
{
	enum Symbol
	{
		oval, squiggle, diamond
	};
	enum Color
	{
		red, green,purple
	};
	enum Number
	{
		one, two, three
	};
	enum Shading
	{
		filled, open, striped
	};
	// Instance variables 
	Symbol s;
	Color c;
	Number n;
	Shading sh;

public:
	//Constructor
	Card();

	Card(string card);
	

	bool create(string card);  // creates a card

	static string getNumber(Number n); // get the number of shapes

	static string getColor(Color c); // gets the color of shapes
	

	static string getSymbol(Symbol s); // gets the shape of the symbol


	static string getShading(Shading sh); // gets the shading


	void display(); // disaplys the card
	

	bool solve(Card c1, Card c2); // solves the card 
	

	bool equals(Card card);
	

	Card solve(Card card);
	
};

