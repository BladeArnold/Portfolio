#include "Node.h"

int Node::degree() const // gets the degree
{
	if (this->left == nullptr && this->right == nullptr)
	{
		return 0;
	}
	if (this->left != nullptr && this->right != nullptr)
	{
		return 2;
	}
	return 1;
}

int userNode::compare(Node* other) // comapre user 
{
	return user.compare(other->user);
}
int ticketNode::compare(Node* other) // comapre ticket
{
	return ticket - (other->ticket);
}

int Node::compare(string user)
{
	return this->user.compare(user);
}
int Node::compare(int ticket)
{
	return this->ticket - ticket;
}
