#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void partitionOddAndEvenin(int *buffer, int num, int ind, int status);

int main (int argc, char *argv[])
{
  int num;
  int * buffer;
  int ind;
  int status;
  //status = 0,odd.  status =1, even.
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
  status =2;
  partitionOddAndEvenin(buffer, num, ind, status);
  
  return EXIT_SUCCESS;
}

void partitionOddAndEvenin(int *buffer, int num, int ind, int status)
{
  int i;
  int h;
  int choice;
  int statusNew;
  if(num == 0)
    {
      for(h=0; h<ind-1; h++)
	{
	  printf("%d + ", buffer[h]);
	}
      printf("%d\n", buffer[h]);
      return;

    }
  for(i=1; i<=num; i++)
    {
      choice = i % 2;
      if(choice ==0)
	{
	  statusNew = 1;
	}
      else
	{
	  statusNew = 0;
	}
      if(status != statusNew)
	{	  
	  buffer[ind] = i;
	  partitionOddAndEvenin(buffer, num-i, ind+1, statusNew);  
	}
    }

}
