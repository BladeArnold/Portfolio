#include "list.hpp"
#include <iostream>
#include <string>

using namespace std;

void reverse (Node **place) // code for the reverse function 
  {
    Node *temp = NULL;
    Node *current = *place;

    while (current != NULL)
      {
	temp = current->prev;
	current->prev = current->next;
	current->next = temp;
	current = current->prev;
	
      }
    if(temp != NULL)
      {
	*place = temp->prev;
      }
  }

void push(Node** place, string new_data) // code for the push function
  {
    Node* new_node = new Node();

    new_node->data = new_data;

    new_node->prev = NULL;

    new_node->next = (*place);

    if (*place != NULL)
      {
	(*place)->prev = new_node;
      }

    (*place) = new_node;
  }

void print(Node *node) // code for the print function
  {
    while (node !=NULL)
      {
	cout << node->data << " ";
	node = node->next;
      }
  }
