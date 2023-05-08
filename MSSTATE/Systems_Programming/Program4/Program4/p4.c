#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <malloc.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include "binary_sem.h"
#include <sys/shm.h>
#include <sys/sem.h>

#define PLAYER1 1
#define PLAYER2 2

int turncounter = 0;
int game[3][3],a,b;

struct mSeg
{
    
  int randnum;
  int vals[2];
};

int checkCall(int val, char *str)
{
  if (val == -1)
    {
      if (val == EINTR) return val;
      perror(str);
      exit(EXIT_FAILURE);
    }
  return val;
}



void initFIFO(char *path)
{
  if (mkfifo(path, S_IRUSR | S_IWUSR) == -1)
    {
      if (errno == EEXIST) return;
      perror("mkfifo");
      exit(EXIT_FAILURE);
    }
  return;
}

int trywin () // checks the game for a win state
{
  int nowin = 0;
  
  for(int i = 0; i < 3; i++)
    {
      if(game[i][0] == game[i][1] || game[i][0] == game[i][2])
	{
	  nowin++;

	}
    }
  
  for(int i = 0; i < 3; i++)
    {
      if(game[0][i] == game[1][i] || game[0][i] == game[2][i])
	{
	  nowin++;

	}
    }
  
  if(game[0][0] == game[1][1] || game[0][0] == game[2][2])
    {
      nowin++;

    }
  if(game[0][2] == game[1][1] || game[0][2] == game[2][0])
    {
      nowin++;

    }

  if (nowin != 0)
  {
     return 0;
  }
  else
  {
     return 1;
  }
}
int displaygame () // should display the game
{
  printf(" %c | %c | %c ", game[0][0], game[0][1], game[0][2]);
   printf("\n -+-+-\n");
   printf(" %c | %c | %c ", game[1][0], game[1][1], game[1][2]);
   printf("\n -+-+-\n");
   printf(" %c | %c | %c ", game[2][0], game[2][1], game[2][2]);
   printf("\n");
}


int player1game()
{
  key_t sharedMemKey, semaphoreKey;
  int semaphoreID, sharedMemID;
  struct mSeg *attachedSharedMem;
  int fd;
  
  
  while(turncounter > -1)
    {
      // reserve the PLAYER1 the semaphore
      reserveSem(semaphoreID, PLAYER1);
      
      displaygame();
      
      if(turncounter == 0)
	{
	  game[1][1] = 'X';
	  break;
	}
	
      else 
      {
      
       if (trywin == 0) // checks all of the spaces to see if other player is about to win
	    {
      	     	for (int i = 0; i < 3; i++)
      	     	{
		  if(game[i][0] == game[i][1] || game[i][0] == game[i][2])
		    {
		      if (game[a][b] == ' ')
			{
			  game[a][b] = 'X';
			  break;
			}
		    }
		}
		
	        for (int i = 0; i < 3; i++)
	        {
		  if(game[0][i] == game[1][i] || game[0][i] == game[2][i])
		    {
		      if (game[a][b] == ' ')
			{
			  game[a][b] = 'X';
			  break;
			}
		    }
		}
	     
	      if(game[0][0] == game[1][1] || game[0][0] == game[2][2])
		{
		  if (game[a][b] == ' ')
		    {
		      game[a][b] = 'X';
		      break;
		    }
		}
		
	      if(game[0][2] == game[1][1] || game[0][2] == game[2][0])
		{
		  if (game[a][b] == ' ')
		    {
		      game[a][b] = 'X';
		      break;
		    }
		}

	    }
	    
	 if (trywin != 0) // if player does not have a win does a random move 
	 {
	  a = rand() % 3;
	  b = rand() % 3;
	  game[a][b] = 'X';
	  break;
	 }
      }

    }
    
  displaygame();
      
  if(turncounter == 8) // ends the game
    {
      turncounter = -1;
      exit(EXIT_SUCCESS);
    } 
    
  releaseSem(semaphoreID, PLAYER2); // release the PLAYER2 semaphore
  exit(EXIT_SUCCESS);
  
}


int player2game()
{
  key_t sharedMemKey, semaphoreKey;
  int semaphoreID, sharedMemID;
  struct mSeg *attachedSharedMem;
  int fd;
  
  
  while (1)
    {
      // reserve the PLAYER2 the semaphore
      reserveSem(semaphoreID, PLAYER2);
      
      displaygame();
      
      if (turncounter == -1)
	{
	  exit(EXIT_SUCCESS);
	}
	
      if (turncounter == 0)
	{
	  game[0][0] = 'O';
	  break;
	}
	
      else 
	{
	  if (trywin == 0) // checks all of the spaces to see if other player is about to win
	    {
      	        for (int i = 0; i < 3; i++)
      	        {
		  if(game[i][0] == game[i][1] || game[i][0] == game[i][2])
		    {
		      if (game[a][b] == ' ')
			{
			  game[a][b] = 'O';
			  break;
			}
		    }
		}
	     for (int i = 0; i < 3; i++)
	     {
		  if(game[0][i] == game[1][i] || game[0][i] == game[2][i])
		    {
		      if (game[a][b] == ' ')
			{
			  game[a][b] = 'O';
			  break;
			}
		    }
	    }
	     
	      if(game[0][0] == game[1][1] || game[0][0] == game[2][2])
		{
		  if (game[a][b] == ' ')
		    {
		      game[a][b] = 'O';
		      break;
		    }
		}
	      if(game[0][2] == game[1][1] || game[0][2] == game[2][0])
		{
		  if (game[a][b] == ' ')
		    {
		      game[a][b] = 'O';
		      break;
		    }
		}

	    }
	 if (trywin != 0) // if player does not have a win does a random move 
	 {
	  a = rand() % 3;
	  b = rand() % 3;
	  game[a][b] = 'O';
	 }
	}
      
      displaygame();
      turncounter++;
      releaseSem(semaphoreID, PLAYER1); // release the PLAYER1 semaphore
    }
}






void player1()
{
  key_t sharedMemKey, semaphoreKey;
  int semaphoreID, sharedMemID;
  struct mSeg *attachedSharedMem;
  int fd;
  int randnum1;
  int randnum2;
  initFIFO("xoSync");
   
  
  randnum1 = rand();
  randnum2 = rand();
 
    
  
  sharedMemKey = ftok("xoSync",randnum1); // generate two keys (ftok)
  semaphoreKey = ftok("xoSync",randnum2);

 
  sharedMemID = checkCall(shmget(sharedMemKey, sizeof(struct mSeg), IPC_CREAT | S_IRUSR | S_IWUSR), "shmget");  // create the shared memory

  
  semaphoreID = checkCall(semget(semaphoreKey, 2, IPC_CREAT | S_IRUSR | S_IWUSR), "shmget"); // create the semaphore 

  

  
  initSemInUse(semaphoreID, PLAYER2); // init the PLAYER2 to "in use"
  
  initSemAvailable(semaphoreID, PLAYER1); //init the PLAYER1 to "available"

  
  attachedSharedMem = (struct mSeg *) shmat(sharedMemID, NULL, 0); // attach the shared memory


  fd = checkCall(open("xoSync", O_WRONLY), "open"); // opens the fifo
  
  checkCall(write(fd, &attachedSharedMem, sizeof(attachedSharedMem)), "write to the pipe"); // writes to the fifo
    
  close(fd); 
  player1game(); // calls the game function
  fd = checkCall(open("xoSync", O_WRONLY), "open"); // opens fifo
  close(fd);
    
  shmdt(attachedSharedMem); // detach the shared memory

  
  checkCall(shmctl(sharedMemID, IPC_RMID, NULL), "shmctl"); // delete the semaphores and shared memory
  checkCall(semctl(semaphoreID, 0, IPC_RMID), "semctl");
    
    
   
}




void player2()
{
  key_t sharedMemKey, semaphoreKey;
  int semaphoreID, sharedMemID;
  struct mSeg *attachedSharedMem;
  char c[1024];
  int fd;
  int randnum1; // key
  int randnum2; // key

  initFIFO("xoSync");


  fd = checkCall(open("xoSync", O_RDONLY), "open");


  checkCall(read(fd, &c, sizeof(c)), "read from the pipe");


  close(fd);
   
  
  sharedMemKey = ftok("xoSync",randnum1); // generate two keys (ftok)
  semaphoreKey = ftok("xoSync",randnum2);
    
  
  sharedMemID = checkCall(shmget(sharedMemKey, 0, 0), "shmget"); // retrieve the semaphores and shared memory
  semaphoreID = checkCall(semget(semaphoreKey, 0, 0), "semget");
    
  attachedSharedMem = (struct mSeg *) shmat(sharedMemID, NULL, 0); // attach the shared memory
    
  player2game(); // calls player 2 game
    
  fd = checkCall(open("FIFOval", O_RDONLY), "open");
    
  close(fd);
    
  shmdt(attachedSharedMem); // detach the shared memory

}



int main ()
{
while (turncounter != 9) // runs the game until the game is done
{
player1();
player2();
}
}
