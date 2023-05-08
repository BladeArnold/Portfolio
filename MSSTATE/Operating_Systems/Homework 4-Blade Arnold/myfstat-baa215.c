//Name: Blade Arnold 
//NetID: baa215
//Program description: This program takes files names from the command line and spits out file info
//To run the program: ./myfstat-baa215 (whatever file names you use)



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/resource.h>

#define maxfiles 50 // the command line can hold up to this many 

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


int main(int argc, char *argv[])
{
    struct rusage usage; // declare the usage struct
    int fd; // file descrp
    int i; // var for for loop
    char **filename = argv + 1; // gets the files names 


    int numberoffiles = argc - 1; // gets the number of files by subtracting ./threads
    if (numberoffiles == 0) // sees if there are files after ./threads 
    {
        printf("Please make sure to enter the file names.\n");
        exit(EXIT_FAILURE);
    }

    if (numberoffiles > maxfiles) // checks to see if the number of files is more than 50
    {
       printf("Too many files!\n");
       exit(EXIT_FAILURE); 
    }


    for (i = 0; i < numberoffiles; i++) // for loop for each input
    {
        fd = checkCall(open(argv[i+1], O_RDONLY), "open"); // opens the files also handle errors for files that are not in the directory

        struct stat fileStat; // decleare the file struct

        checkCall(fstat(fd,&fileStat), "fstat"); // call fstat to get the stats of the files


        if (S_ISREG(fileStat.st_mode))  // checks to see if it is a file
        {
            int j; // keeps track of the files
            j++; // adds to the counter
            printf("%s is a file! File %d\n", argv[i+1],j); //prints out file name
            printf("----------------------------\n"); // for cleanliness 
            printf("User ID: %d \n",fileStat.st_uid); // uses fstat to get the user id
            printf("Group ID: %d \n",fileStat.st_gid); // uses fstat to get the group id
            printf("Number of links: %ld \n",fileStat.st_nlink); // uses fstat to get the number of links
            printf("Last time file was accessed: %ld \n",fileStat.st_atime); // uses fstat to get the last time file was accessed
            printf("Time of last modification: %ld \n",fileStat.st_mtime); // uses fstat to get the time of last modification
            printf("Time of last status: %ld \n",fileStat.st_ctime); // uses fstat to get the time of last status
            printf("File Size: %ld bytes\n",fileStat.st_size); // uses fstat to get the file size in bytes
            printf("File Inodes: %ld \n",fileStat.st_ino); // uses fstat to get the file inodes
            printf("----------------------------\n"); // for cleanliness
        }

        else if (S_ISDIR(fileStat.st_mode)) // checks to see if it is a directory
        {
            int q; // keeps track of number of directories
            q++; // adds to the counter
            printf("%s is a directory!! Directory %d\n", argv[i+1],q); //prints out directory name
            printf("----------------------------\n"); // for cleanliness 
            printf("User ID: %d \n",fileStat.st_uid); // uses fstat to get the user id
            printf("Group ID: %d \n",fileStat.st_gid); // uses fstat to get the group id
            printf("Number of links: %ld \n",fileStat.st_nlink); // uses fstat to get the number of links
            printf("Last time directory was accessed: %ld \n",fileStat.st_atime); // uses fstat to get the last time directory was accessed
            printf("Time of last modification: %ld \n",fileStat.st_mtime); // uses fstat to get the time of last modification
            printf("Time of last status: %ld \n",fileStat.st_ctime); // uses fstat to get the time of last status
            printf("Directory Size: %ld bytes\n",fileStat.st_size); // uses fstat to get the directory size in bytes
            printf("Directory Inodes: %ld \n",fileStat.st_ino); // uses fstat to get the directory inodes
            printf("----------------------------\n"); // for cleanliness
        }


        checkCall(close(fd),"close"); // closes the file or directory 
    }

    checkCall(getrusage(RUSAGE_SELF, &usage), "usage"); // call getrusage to get system and user info

    printf("User cpu time: %ld.%06lds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec); // prints the user time 
    printf("System cpu time: %ld.%06lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec); // prints the system time


    return 0;
}