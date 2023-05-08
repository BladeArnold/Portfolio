#pragma once
#include <string>
using namespace std;

class Node
{
public:
	string user;
	int ticket;
	Node* left;
	Node* right;
	Node() : user(""),ticket(-1), left(nullptr), right(nullptr) {}
	Node(string user, int ticket) : user(user), ticket(ticket), left(nullptr), right(nullptr) {}
	virtual ~Node() {}
	int degree() const;
	virtual int compare(Node* other) = 0;
	virtual int compare(string user);
	virtual int compare(int ticket);
};

class userNode :public Node
{
public:
	userNode(string user, int ticket) : Node(user, ticket) {}
	int compare(Node* other);
};

class ticketNode :public Node
{
public:
	ticketNode(string user, int ticket) : Node(user, ticket) {}
	int compare(Node* other);
};