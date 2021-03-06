#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void partitionIncreasing(int *buffer, int num, int ind, int small);

int main (int argc, char *argv[])
{
  int num;
  int * buffer;
  int ind;
  int small = 1;
  
  if(argc < 2)
    {
      return EXIT_FAILURE;
    }
  if(argv[1]<0)
    {
      return EXIT_FAILURE;
    }
  
  num = (int) strtol(argv[1], NULL, 10);
  buffer = malloc(sizeof(int) * num);
  ind=0;
  partitionIncreasing(buffer, num, ind, small);
  
  return EXIT_SUCCESS;
}

void partitionIncreasing(int *buffer, int num, int ind, int small)
{
  int i;
  int h;
  if(num == 0)
    {
      for(h=0; h<ind-1; h++)
	{
	  printf("%d + ", buffer[h]);
	}
      printf("%d\n", buffer[h]);
      return;

    }
  for(i=small; i<=num; i++)
    {
      buffer[ind] = i;
      partitionIncreasing(buffer, num-i, ind+1, i+1);
    }
}

  
