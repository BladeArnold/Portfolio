#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

int main (int argc, char *argv[])
{

    pid_t cPid; // makes the child id 

    cPid = checkCall(fork(),"fork"); // makes the child 

    int ccounter = 0; // child counter
    int pcounter = 0; // parent counter 

    switch (cPid) // to go between child and parent 
    {
        case 0: // child  case
            for (int j = 1; j < 21; j++) // loops 20 times and spits out counter for child
            {
                ccounter++; 
                printf("Child: %d\n", ccounter);
            }
        default: // parent case 
            for (int i = 1; i < 21; i++) // loops 20 times and spits out counter for parent
            {
                pcounter++;
                printf("Parent: %d\n", pcounter);
            }
    }

    exit(EXIT_SUCCESS);
}