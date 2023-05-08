#include "Card.h"
#include <iostream>
#include <string>

using namespace std;

	//Constructor
	Card::Card()
	{

	}
	Card::Card(string card)
	{
		create(card);
	}

	bool Card::create(string card)  // creates a card
	{
		if (card.length() != 4)
		{
			cerr << "Card must have four charecters." << endl;
			return false;
		}
		switch (card[0])
		{
		case '1': this->n = one;
			break;
		case '2': this->n = two;
			break;
		case '3': this->n = three;
			break;
		default: cerr << "Invalid number " << endl;
			return false;
		}

		switch (card[1]) // color part of card
		{
		case 'G': this->c = green;
			break;
		case 'P': this->c = purple;
			break;
		case 'R': this->c = red;
			break;
		default: cerr << "Invalid color " << endl;
			return false;
		}

		switch (card[2]) // filling of the card
		{
		case 'F': this->sh = filled;
			break;
		case 'O': this->sh = open;
			break;
		case 'S': this->sh = striped;
			break;
		default: cerr << "Invalid shading " << endl;
			return false;
		}

		switch (card[3]) // shape of the card
		{
		case 'D': this->s = diamond;
			break;
		case 'O': this->s = oval;
			break;
		case 'S': this->s = squiggle;
			break;
		default: cerr << "Invalid Symbol" << endl;
			return false;
		}

		return true;
	}

	 string Card::getNumber(Number n) // get the number of shapes
	{
		switch (n)
		{
		case one: return "1";
		case two: return "2";
		case three: return "3";
		default: return "*";
		}
	}

	 string Card::getColor(Color c) // gets the color of shapes
	{
		switch (c)
		{
		case purple: return "purple";
		case green: return "green";
		case red: return "red";
		default: return "*";
		}
	}

	 string Card::getSymbol(Symbol s) // gets the shape of the symbol
	{
		switch (s)
		{
		case diamond: return "diamond";
		case oval: return "oval";
		case squiggle: return "squiggle";
		default: return "*";
		}
	}

	 string Card::getShading(Shading sh) // gets the shading
	{
		switch (sh)
		{
		case filled: return "filled";
		case open: return "open";
		case striped: return "striped";
		default: return "*";
		}
	}

	void Card::display() // disaplys the card
	{
		printf("%s %+6s %+7s %+8s ", getNumber(n).c_str(), getColor(c).c_str(), getShading(sh).c_str(), getSymbol(s).c_str());
	}

	bool Card::solve(Card c1, Card c2) // solves the card 
	{
		bool samenumber = (n == c1.n && n == c2.n);
		bool samesymbol = (s == c1.s && s == c2.s);
		bool samecolor = (c == c1.c && c == c2.c);
		bool sameshading = (sh == c1.sh && sh == c2.sh);
		bool uniquenumber = (n != c1.n && n != c2.n && c1.n != c2.n);
		bool uniquesymbol = (s != c1.s && s != c2.s && c1.s != c2.s);
		bool uniquecolor = (c != c1.c && c != c2.c && c1.c != c2.c);
		bool uniqueshading = (sh != c1.sh && sh != c2.sh && c1.sh != c2.sh);

		if (uniquenumber && uniquesymbol && uniquecolor && uniqueshading)
		{
			return true;
		}
		int count = 0;
		if (samenumber)
		{
			count++;
		}

		else if (!uniquenumber)
		{
			return false;
		}
		if (samesymbol)
		{
			count++;
		}
		else if (!uniquesymbol)
		{
			return false;
		}

		if (samecolor)
		{
			count++;
		}
		else if (!uniquecolor)
		{
			return false;
		}

		if (sameshading)
		{
			count++;
		}
		else if (!uniqueshading)
		{
			return false;
		}

		return(count == 2 || count == 1 || count == 3);

	}

	bool Card::equals(Card card)
	{
		if (this->n != card.n)
		{
			return false;
		}
		if (this->c != card.c)
		{
			return false;
		}
		if (this->s != card.s)
		{
			return false;
		}
		if (this->sh != card.sh)
		{
			return false;
		}
		return true;
	}


	Card Card::solve(Card card)
	{
		Card c3;
		if (n == card.n)
		{
			c3.n = n;
		}
		else
		{
			for (int number = one; number != three; number++)
			{
				if (number != n && number != card.n)
				{
					c3.n = (Number)number;
					break;
				}
			}
		}
		if (s == card.s)
		{
			c3.s = s;
		}
		else
		{
			for (int symbol = oval; symbol != diamond; symbol++)
			{
				if (symbol != s && symbol != card.s)
				{
					c3.s = (Symbol)symbol;
					break;
				}
			}

		}
		if (c == card.c)
		{
			c3.c = c;
		}
		else
		{

			for (int color = red; color != purple; color++)
			{
				if (color != c && color != card.c)
				{
					c3.c = (Color)color;
					break;
				}
			}

		}
		if (sh == card.sh)
		{
			c3.sh = sh;
		}
		else
		{

			for (int shading = filled; shading != striped; shading++)
			{
				if (shading != sh && shading != card.sh)
				{
					c3.sh = (Shading)shading;
					break;
				}
			}


		}
		return c3;
	}


