//Name: Blade Arnold 
//NetID: baa215
//Program description: This program takes files names from the command line and count the number lines
//To run the program: ./baa215-linecount (whatever file names you use) or ./threads (whatever file names you use)


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define buffersize 2048 // buffer size for the read statement
#define maxfiles 64 // the command line can hold up to this many 

// variable intialization 
pthread_t tid[maxfiles];
int totalcount; 
pthread_mutex_t lock;


int checkCall(int val, const char *str) // check call from systems class
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



int update_total(int total) // add the linecount to the toatl counter 
{
    checkCall(pthread_mutex_lock(&lock), "lock");  // locks the mutex

    totalcount += total; // adds the total counter 

    checkCall(pthread_mutex_unlock(&lock), "unlock");  // unlocks the mutex

    return totalcount; // returns the total 
}

void count_line(char* file) // counts the line in the files that are given in the command line
{
    int fd; // file desc
    int readnum; // read desc
    char buffer[buffersize]; // buffer and its size 
    int linecount = 0; //
    int i;
    

    fd = checkCall(open(file, O_RDONLY), "open"); // opens the files 

    while ((readnum = checkCall(read(fd, buffer, buffersize), "read")) > 0) // reads the files
    {
        for (i = 0; i < readnum; i++) // adds to the line count
        {
            if (buffer[i] == '\n')
            {
                linecount++;
            }
        }
    }

    checkCall(close(fd), "close"); // closes the file 

    printf("%s: %d lines\n", file, linecount); // print the file and line count 

    update_total(linecount); // calls the update total with the file line count 
}
  

  
int main(int argc, char *argv[])
{
    int i;

    int numberoffiles = argc - 1; // gets the number of files by subtracting ./threads
    if (numberoffiles == 0) // sees if there are files after ./threads 
    {
        printf("Please make sure to enter the file names.\n");
        exit(EXIT_FAILURE);
    }

    char **filename = argv + 1; // gets the files names 


    for (i = 0; i < numberoffiles; i++) // creates threads for the files 
    {
        pthread_create(&tid[i], NULL, (void *(*)(void *))count_line, (void *)filename[i]);  
    }
  
    for (i = 0; i < numberoffiles; i++) // join all the threads 
    {
        pthread_join(tid[i], NULL);
    }
    
    pthread_mutex_destroy(&lock); // destroys the mutex

    printf("Total lines: %d\n",totalcount); // prints the total lines 
  
    exit(EXIT_SUCCESS);

    return 0;
}