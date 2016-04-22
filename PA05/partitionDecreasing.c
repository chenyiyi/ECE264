#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void partitionDecreasingin(int *buffer, int num, int ind, int big);

int main (int argc, char *argv[])
{
  int num;
  int * buffer;
  int ind;
  int big ;
  
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
  big = num;
  ind=0;
  partitionDecreasingin(buffer, num, ind, big);
  
  return EXIT_SUCCESS;
}

void partitionDecreasingin(int *buffer, int num, int ind, int big)
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
  for(i=big; i>0; i--)
    {
      buffer[ind] = i;
      partitionDecreasingin(buffer, num-i, ind+1, i-1);  
    }

}
