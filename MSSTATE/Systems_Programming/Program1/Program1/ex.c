#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main()
{
  char *arr[5];
  char buf[1024];
  int i, len;

  printf("Please enter 5 words\n");

  for (i = 0; i < 5; i++)
    {
      printf("Word %d: ", i+1);
      scanf("%s", buf);
      //len = strlen(buf);
      //arr[i] = (char *) malloc(sizeof(char) * (len + 1));
      //strcpy(arr[i], buf);
    }

  printf("....\n");

  for(i = 5; i > 0; i--)
    {
      if (strcmp(arr[i-1], "SKIP") == 0) continue;
      printf("Word %d: %s\n", i, arr[i-1]);
    }

  return 0;
}
