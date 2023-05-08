//Baa215 2/21/23
//Description: This program will make a personal shell and run some of the more basic commands in linux
// Operation systems TTH 3:30 Tom Ritter
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#define linelen 257 //the line lenght of the command line 
#define historysize 10 // The amount commands that history can hold 

char prompt[] = "myshell> ";
char history[historysize][linelen];
int historycmd = 0;

int checkCall(int val, char *str) // check call from systems class
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

void sighandler(int sig) // When sigusr1 is passed prints out the history commands in audit log code from examples and systems
{
    int historycmd2 = historycmd;

    if (sig == SIGUSR1)
    {
        int fileout = checkCall(open("audit.log", O_WRONLY | O_TRUNC | O_CREAT, 0644),"open"); // creates the file
         for (int i = 0; i < historysize; i++)
        {
            checkCall(write(fileout, history[i], strlen(history[i])), "write"); // writes into the file
            
        }

        close(fileout);
        exit(EXIT_SUCCESS);
    }
}



int main(int argc, char *argv[])
{
    char line[linelen]; // makes the line for the command line 
    char **mycmd; // declares the mycmd variable 
    mycmd=(char **) malloc( 2 * sizeof(char *)); // makes the space for the command line 
    pid_t pid; // the parenet id 

    signal(SIGUSR1, sighandler); // calls sigusr1

    fprintf(stderr, "%s", prompt); // prints the first prompts

    while (fgets(line, linelen, stdin) != NULL) // the command line loop
    {

        if (historycmd < historysize) // puts the commands into the history 
        {
            strcpy(history[historycmd], line);
            historycmd++;
        } 

        mycmd[0] = strtok(line, " \t\n"); // grabs the commands 

        int numcmd = 1; // commnads after the first one

        while (mycmd[numcmd-1] != NULL) // the command parser 
        {
            mycmd[numcmd] = strtok(NULL, " \t\n");
            numcmd++;
        }

        int back = 0; // see if we are in the back ground
        if (strcmp(mycmd[numcmd-2], "&") == 0) // looks to see if we run in the backgroup
        {
            back = 1;
            
            mycmd[numcmd-2] = NULL;
            numcmd--;
        }

        switch(pid = fork()) // switch statement for the child and parent 
        {
            case 0:
                if (strcmp(mycmd[0], "ls") == 0) // executes the ls command ex: ls -l /usr
                {
                    checkCall(execvp(mycmd[0], mycmd), "execvp");
                }

                if (strcmp(mycmd[0], "cd") == 0) // executes the cd command and show that it did cd correctly ex: cd .. or cd ex
                {
                    char s [100];
                    checkCall(chdir(mycmd[1]), "chdir"); 
                    printf("%s\n",getcwd(s, sizeof(s)));
                    break;
                }

                if (strcmp(mycmd[0], "history") == 0) // executes the history command ex: history
                {
                    int count = 1; // helps the command  print in order
                    int historycmd3 = historycmd; // helps the kill and history command not get confused 
                    for (int i = 0; i < historysize; i++) //prints all the commands 
                    {
                        if (strcmp(history[i], "") != 0)
                        {
                            printf("%d %s", count, history[i]);
                            count++;
                            historycmd3--;
                        }
                    }
                    break;
                }

                if (strcmp(mycmd[0], "env") == 0) // executes the env command ex: env
                {
                    checkCall(execvp(mycmd[0], mycmd), "execvp");
                }

                if (strcmp(mycmd[0], "pwd") == 0) // executes the pwd command ex: pwd
                {
                    checkCall(execvp(mycmd[0], mycmd), "execvp");
                }

                if (strcmp(mycmd[0], "ps") == 0) // executes the ps command ex: ps
                {
                    checkCall(execvp(mycmd[0], mycmd), "execvp");
                }

                if (strcmp(mycmd[0], "kill") == 0) // executes the kill command ex: kill pid
                {
                    pid_t pid = atoi(mycmd[1]);
                    
                    checkCall(kill(pid, SIGUSR1), "kill");
                    break;
                }

                if (strcmp(mycmd[0], "cp") == 0) // executes the cp command ex: cp audit.log audit.txt
                {
                  checkCall(execvp(mycmd[0], mycmd), "execvp");
                }

                if (strcmp(mycmd[0], "sort") == 0) // executes the sort command ex: sort ...
                {
                  checkCall(execvp(mycmd[0], mycmd), "execvp");
                }

                else
                {
                    fprintf(stderr, "ERROR: %s no such program\n", mycmd[0]); // checks for wrong commands
                    exit(EXIT_FAILURE);
                }
                break;
            case -1: 
                fprintf(stderr, "ERROR: can't create child process!\n");
                exit(EXIT_FAILURE);
                break;
            default:
                if (back == 1) // tells to run in background
                {
                    back = 0;
                    break;
                } 
                else 
                {
                    wait(NULL);
                    break;
                }
               
        }

        fprintf(stderr, "%s", prompt);
    }

    exit(EXIT_SUCCESS);
}
