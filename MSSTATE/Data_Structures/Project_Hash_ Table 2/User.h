#pragma once
#include <string>

using namespace std;

class User
{
public:
	User() : userid(""), pwd("")
	{
		modify = false;
	}
	User(string userid, string pwd) : userid(userid), pwd(pwd)
	{
		direct = "/users/" + userid;
		modify = false;
	}
	User(istream& in)
	{
		string mod;
		in >> mod;
		modify = (mod == "M");
		in >> userid;
		in >> pwd;
		in >> direct;
	}

	void savepwd(ostream& out)
	{
		if (modify)
		{
			out << "M" << "\t";
		}
		else
		{
			out << "N" << "\t";
		}
		out << userid << "\t" << pwd << "\t" << direct << "\t";
	}
	friend ostream& operator << (ostream& os, const User& user)
	{
		os << setw(10) << left << user.userid << setw(20) << left << user.direct;
		if (user.userid != "")
		{
			os << setw(10) << right << "*";
		}

		return os;
	}
	string getid()
	{
		return userid;
	}
	void changehome(string homedir)
	{
		direct = homedir;
		modify = true;
	}
	void changepwd(string pwd)
	{
		this->pwd = pwd;
		modify = true;
	}
	string getpwd()
	{
		return pwd;
	}
	bool ismodified()
	{
		return modify;
	}

private:
	string userid;
	string pwd; 
	string direct; 
	bool modify;
};