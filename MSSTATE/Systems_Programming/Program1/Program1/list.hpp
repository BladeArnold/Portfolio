#include <iostream>
#include <bits/stdc++.h>
#include <string>
#pragma once
using namespace std;

class Node // class for nodes in list
{
public:
  string data;
  Node* next;
  Node* prev;

  void reverse (Node **place); // reverse function in list.cpp

  void push(Node** place, string new_data); // push function in list.cpp

  void print(Node *node);  // print function in list.cpp
};
