#include "list.h"
#include "list.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main()
{
  struct Node* head = NULL; // makes the list
  int wordcount; // numbers of words you want
  int i, len; // loop var
  char words[1024]; // string for input



  
  printf("\nPlease enter the number of words you would like\n");
  scanf("%d", &wordcount); // asks and gets the input

  
  for (int i = 0; i < wordcount; i++) // loops throught input of words and pushes them
    {
      printf("\nPlease enter your words. %d ",i+1);
      scanf("%s", words);
      len = strlen(words); 
      // head[i] = (head *) malloc(sizeof(char) * (len + 1));
      // strcpy(head[i], words);
       if (words == "STOP") // breaks out of the loop
       {
        break;
	
       }
      push(&head, words);
      
    }



  
  printf("\nHere is your input.\n");

  
  reverse(&head); //idk why but have to reverse here to get correct order
  print(head); // prints the current order of string


  
  printf("\nHere is the reverse of your string.\n");
  reverse(&head); // reverse the current order

  
  print(head); // prints the current order
  printf("\n");

  
  return 0;  
}
