#pragma once
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template <typename Node, typename Index>
class BST
{
private:
	Node* root;
	bool add(Node*& node, Node* newnode);
	bool remove(Node*& node, Node* data);
	bool find(Node*& node, Index data);
	ostream& inOrder(Node* node, ostream& os);
	ostream& preOrder(Node* node, ostream& os);
	ostream& postOrder(Node* node, ostream& os);
	void destroy(Node* node);
public:
	BST() : root(nullptr) {}
	~BST();
	bool add(Node*& newnode);
	bool remove(Node* data);
	bool find(Index data);
	ostream& inOrder(ostream& os);
	ostream& preOrder(ostream& os);
	ostream& postOrder(ostream& os);
	void destroy();

};
#include"BST.cpp"