/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main(void)
{
 int x;
 
 printf("Enter an integer:");
 scanf("%d", &x);
 
 for (int i=0; i<x; i++)
 {
    for (int j=0; j<x-i; j++)
    {
        printf(" ");
    }
    for(int j=0; j<i; j++)
    {
        printf("* ");
    }
    printf ("\n");
 }
 for (int i=0; i<x; i++)
 {
     for (int j=0; j<i; j++)
        {
         printf(" ");
        }
        
     for (int j=0; j<x-i; j++)
    {
         printf("* ");
    }
 
      printf("\n");
 } 
 
 return 0;
}
