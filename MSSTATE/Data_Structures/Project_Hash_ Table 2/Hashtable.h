#pragma once
#include "User.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <unordered_set>
#define INTSIZE 23
using namespace std;

class Hashtable
{
public:
	Hashtable(int size = INTSIZE)
	{
		create(size);
	}
	void create(int size)
	{
		this->size = size;
		table = new User * [size];
		for (int i = 0; i < size; i++)
		{
			table[i] = nullptr;
		}
		num = 0;
	}
	bool add(string userid, string pwd) 
	{
		int found = find(userid);
		if (found >= 0)
		{
			return false;
		}
		if (num == size)
		{
			resize(2*size);
		}
		size_t index = hash(userid);
		while (table[index] != nullptr)
		{
			index = (index + 1) % size;
		}
		++num;
		table[index] = new User(userid, pwd);
		return true;
	}
	bool add(User* user)
	{
		int found = find(user->getid());
		if (found >= 0)
		{
			return false;
		}
		if (num == size)
		{
			resize(2*size);
		}
		size_t index = hash(user->getid());
		while (table[index] != nullptr)
		{
			index = (index + 1) % size;
		}
		++num;
		table[index] = user;
		return true;
	}
	int find(string userid)
	{
		size_t index = hash(userid);
		int count = 0;

		while (table[index] != nullptr && table[index]->getid() != userid)
		{
			index = (index + 1) % size;
			count++;
			if (count == size)
			{
				return -1;
			}
		}
		if (table[index] == nullptr)
		{
			return -1;
		}
		return index;
	}

	void resize(size_t newsize)
	{
		User** oldtable = table;
		int oldsize = size;
		int oldnum = num;
		create(newsize);

		for (int i = 0; i < oldsize; i++)
		{
			if (oldtable[i] != nullptr)
			{
				add(oldtable[i]);
			}
		}
		delete[] oldtable;
	}

	void printheader(ostream& os) const
	{
		os << setw(10) << " " << setw(10) << left << "mod" << setw(10) << left << "userid" << setw(20) << left << "home Dir"
			<< setw(10) << right << "Pwd" << endl;
	}

	void readpwd(istream& in)
	{
		string tmp;
		while (in.good())
		{
			
			User* user = new User(in);
			getline(in, tmp);
			add(user);
		}
	}

	void savepwd(ostream& out)
	{
		string tmp;
		for (size_t i = 0; i < size; i++)
		{
			if (table[i] != nullptr)
			{
				table[i]->savepwd(out);
				out << endl;
			}
			
		}
	}

	friend ostream& operator << (ostream& os, const Hashtable& table)
	{
		table.printheader(os);
		for (size_t i = 0; i < table.size; i++)
		{
			os << setw(10) << left << i;
			
			if (table.table[i] != nullptr)
			{
				//os << setw(10);
				if (table.table[i]->ismodified())
				{
					os << setw(10) << left <<"M";
				}
				else
				{
					os << setw(10) << left << " ";
				}
				os << *table.table[i];
			}
			os << endl;
		}
		return os;
	}
	bool changehome(string userid, string homedir)
	{
		size_t index = find(userid);
		if (index < 0)
		{
			return false;
		}
		table[index]->changehome(homedir);
	}
	bool changepwd(string userid, string pwd)
	{
		size_t index = find(userid);
		if (index < 0)
		{
			return false;
		}
		table[index]->changepwd(pwd);
	}
	bool verify(string userid, string pwd)
	{
		size_t index = find(userid);
		if (index < 0)
		{
			return false;
		}
		return (table[index]->getpwd() == pwd);
	}
	bool remove(string userid)
	{
		size_t index = find(userid);
		if (index < 0)
		{
			return false;
		}
		delete table[index];
		table[index] = nullptr;
	}
	void clear()
	{
		for (size_t i = 0; i < size; i++)
		{
			if (table[i] != nullptr)
			{
				delete table[i];
			}

		}
		delete[] table;
		create(INTSIZE);
	}
	void printuser(string userid)
	{
		size_t index = find(userid);
		if (index < 0)
		{
			cout << userid << " not found." << endl;
		}
		else
		{
			cout << "That user was found." << endl;
			cout << endl;
			printheader(cout);
			cout << *table[index] << endl;
		}
	}
private:
	size_t size; 
	size_t num; 
	User** table;

	size_t hash(string key)
	{
		size_t sum = 0;
		for (size_t i = 0; i < key.size(); i++)
		{
			sum += (size_t)key[i];
		}
		return sum % size;
	}
};