#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#pragma once



struct Node
{
  char data;
  struct Node *next;
  struct Node *prev;


};

  
  void reverse (struct Node **place); // reverse function in list.c

  void push (struct Node** place, char* new_data); // reverse function in list.c

  void print (struct Node *node); // print function in list.c 
