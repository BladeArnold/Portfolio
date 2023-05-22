#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#pragma once

void reverse (struct Node **place) // code for the reverse function 
  {
    struct Node *temp = NULL;
    struct Node *current = *place;

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

void push(struct Node** place, char* new_data) // code for the push function
  {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    new_node->data = *new_data;

    new_node->prev = NULL;

    new_node->next = (*place);

    if (*place != NULL)
      {
	(*place)->prev = new_node;
      }

    (*place) = new_node;
  }

void print(struct Node *node) // code for the print function
  {
    while (node !=NULL)
      {
	printf("%d ", node->data);
	node = node->next;
      }
  }
