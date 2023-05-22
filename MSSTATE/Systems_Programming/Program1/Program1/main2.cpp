#include <iostream>
#include "list.hpp"
#include "list.cpp"
#include <bits/stdc++.h>
#include <string>

using namespace std;

int main()
{
  Node* head = NULL; // makes the list
  int wordcount; // numbers of words you want
  int i = 0; // loop var
  string words; // string for input



  
  cout << "Please enter the number of words you would like."<< endl;
  cin >> wordcount; // asks and gets the input



  
  
  for (int i = 0; i < wordcount; i++) // loops throught input of words and pushes them
    {
      cout << "Please enter your words. " << (i+1) <<"/" << wordcount  << " " << endl;
      cin >> words;
      if (words == "STOP") // breaks out of the loop
	{
	  break;
	
	}
      push(&head,words);
      
    }



  
  cout << "Here is your input." << endl;

  
  reverse(&head); //idk why but have to reverse here to get correct order
  print(head); // prints the current order of string

  
  cout << endl;


  
  cout << "Here is the reverse of your string." << endl;
  reverse(&head); // reverse the current order

  
  print(head); // prints the current order

  
  cout << endl;

  
  return 0;
}
