#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>





// implement three threads ...
// one prints evens
// one that prints odds
// main thread



int threaderror(int err, char* str)
{
    if (err > 0)
    {
        errno = err;
        perror(str);
        exit(EXIT_FAILURE);
    }
    return err;
}



void* eventhread(void* args)
{
    int n = 0;
    struct timespec tv;
    pthread_t tid;

    tid = pthread_self();

    threaderror(pthread_detach(tid), "pthread_detach");


    tv.tv_sec = 1;
    tv.tv_nsec = 0;

    for (n = 0; n < 61; n += 2)
    {
        printf("E: %d\n", n);
        nanosleep(&tv, NULL);
    }
    pthread_exit(NULL);
}





void* oddthread(void* args)
{
    int n = 1;
    struct timespec tv;
    pthread_t tid;

    tid = pthread_self();

    threaderror(pthread_detach(tid), "pthread_detach");

    tv.tv_sec = 1;
    tv.tv_nsec = 0;

    for (n = 1; n < 61; n += 2)
    {
        printf("O: %d\n", n);
        nanosleep(&tv, NULL);
    }
    pthread_exit(NULL);
}







int main(int argc, char* argv[])
{
    pthread_t tid[2];
    int err;
    struct timespec tv;
    tv.tv_sec = 40;
    tv.tv_nsec = 0;



    // create threads
    threaderror(pthread_create(&tid[0], NULL, eventhread, NULL), "pthread_create");
    threaderror(pthread_create(&tid[1], NULL, oddthread, NULL), "pthread_create");



    // detach the threads here
    threadError(pthread_detach(tid[0]), "pthread_detach");
    threadError(pthread_detach(tid[1]), "pthread_detach");



    // join threads
    threadError(pthread_join(tid[0], NULL), "pthread_join");
    threadError(pthread_join(tid[1], NULL), "pthread_join");

    nanosleep(&tv, NULL);
}