#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void partitionEvenin(int *buffer, int num, int ind);

int main (int argc, char *argv[])
{
  int num;
  int * buffer;
  int ind;
  
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
  partitionEvenin(buffer, num, ind);
  
  return EXIT_SUCCESS;
}

void partitionEvenin(int *buffer, int num, int ind)
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
  for(i=2; i<=num; i=i+2)
    {
      buffer[ind] = i;
      partitionEvenin(buffer, num-i, ind+1);  
    }

}
