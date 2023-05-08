#include "BST.h"
#include <string>
#ifndef _BST__CPP_
#define _BST__CPP_

template <typename Node, typename Index>

BST <Node, Index> ::~BST() // bst tree
{
}

template <typename Node, typename Index> // returns add 
bool BST<Node, Index>::add(Node*& newnode)
{
	return add(root, newnode);
}

template <typename Node, typename Index>
bool BST<Node, Index>::remove(Node* data) // returns remove
{
	return remove(root, data);
}

template <typename Node, typename Index>
bool BST<Node, Index>::find(Index data) // returns find
{
	return find(root, data);
}

template <typename Node, typename Index>
ostream& BST<Node, Index>::inOrder(ostream& os) // finds inorder
{
	 inOrder(root, os);
	os << endl;
	return os;
}

template <typename Node, typename Index>
ostream& BST<Node, Index>::preOrder(ostream& os) // finds preorder
{
	preOrder(root, os);
	os << endl;
	return os;
}

template <typename Node, typename Index>
ostream& BST<Node, Index>::postOrder(ostream& os)// finds postorder
{
	postOrder(root, os);
	os << endl;
	return os;
}

template <typename Node, typename Index>
void BST<Node, Index>::destroy() // destroys root
{
	return destroy(root);
}

template <typename Node, typename Index>
bool BST<Node, Index>::add(Node*& node, Node* newnode) // inserts data in to the tree
{
	if (node == nullptr)
	{
		node = newnode;
		return true;
	}

	if (newnode->compare(node) < 0)
	{
		return add(node->left, newnode);
	}

	if (newnode->compare(node) > 0)
	{
		return add(node->right, newnode);
	}

	if (newnode->compare(node) == 0)
	{
		cout << "Information is already in the tree." << endl;
	}
	return false;
}

template <typename Node, typename Index>
bool BST<Node, Index>::remove(Node*& node, Node* data) // removes the data from the tree 
{
	if (node == nullptr)
	{
		return false;
	}

	if (node->compare(data) > 0)
	{
		return remove(node->left, data);
	}
	if (node->compare(data) < 0)
	{ 
		return remove(node->right, data);
	}

	int deg = node->degree();  // degree of the node

	if (deg == 0)
	{
		delete node;
		node = nullptr;
	}

	else if (deg == 1)
	{
		Node* tmp = node;

		if (node->left != nullptr)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
		delete tmp;
	}
	else
	{
		
		Node* tmp = node->left;
		while (tmp->right != nullptr)
		{
	
			tmp = tmp->right;
		}
		node->user = tmp->user;
		node->ticket = tmp->ticket;

		remove(node->left, tmp);
	}
	return true;
}

template <typename Node, typename Index>
ostream& BST<Node, Index>::postOrder(Node* node, ostream& os) // puts data in postorder
{
	if (node == nullptr) return os;
	postOrder(node->left, os);
	postOrder(node->right, os);
	os << node->user << " @ " << node->ticket << " ";
	return os;
}

template <typename Node, typename Index>
void BST<Node, Index>::destroy(Node* node) // destroy node
{
	if (node->left != nullptr)
	{
		destroy(node->left);
	}
	if (node->right != nullptr)
	{
		destroy(node->right);
	}
	delete node;
}

template <typename Node, typename Index>
ostream& BST<Node, Index>::inOrder(Node* node, ostream& os) // puts the data in order
{
	if (node == nullptr) return os;
	inOrder(node->left, os);
	os << node->user << " @ " << node->ticket << " ";
	inOrder(node->right, os);
	return os;
}

template <typename Node, typename Index>
ostream& BST<Node, Index>::preOrder(Node* node, ostream& os) // puts the data in pre order
{
	if (node == nullptr) return os;
	os << node->user << " @ " << node->ticket << " ";
	preOrder(node->left, os);
	preOrder(node->right, os);
	return os;
}

template <typename Node, typename Index>
bool BST<Node, Index>::find(Node*& node, Index data) // finds node
{
	if (node == nullptr || node->compare(data) == 0)
	{
		cout << node->user << " @ " << node->ticket << " has been found." << endl;
		
	}

	if (node->compare(data) > 0)
	{
		cout << find(node->right, data) << " has been found." << endl;
	}

	if (node->compare(data) < 0)
	{
		cout << find(node->left, data) << " has been found." << endl;
	}

	else
	{
		cout << "The information you were looking for is not here." << endl;
	}
	return false;
}

#endif

