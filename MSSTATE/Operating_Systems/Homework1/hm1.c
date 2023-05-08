#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <errno.h>

int checkCall(int val, char *str) // ths checks all call functions...code from my systems class
{
    if (val == -1)
    {
        if (val == EINTR) 
        {
            return val;
        }
        perror(str);
        exit(EXIT_FAILURE);
    }
    return val;
}



int main (int argc, char *argv[50])
{
    char *mycmd[50] = {"ls", "-l", "/usr", NULL}; // commands to be inputed
    checkCall(execvp(mycmd[0], mycmd), "execvp"); // calls the check call function and makes sures execvp executes correctly
   

    exit(EXIT_SUCCESS); // lets the program know that it exited 
}