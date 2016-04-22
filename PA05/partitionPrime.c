#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
void partitionPrimein(int *buffer, int num, int ind);
int checkprime(int val);

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
  partitionPrimein(buffer, num, ind);
  
  return EXIT_SUCCESS;
}

void partitionPrimein(int *buffer, int num, int ind)
{
  int i;
  int h;
  int check;
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
      if(i != 1)
	{
	  check = checkprime(i);
	  if(check==0)
	    {
	      buffer[ind] = i;
	      partitionPrimein(buffer, num-i, ind+1); 
	    } 
	}	
    }

}

int checkprime(int val)
{
  int i;
  int check=0;
  int mod;
  for(i=2; i<val; i++)
    {
      mod = val % i;
      if(mod ==0)
	{
	  check =1;
	  break;
	}
    }
  return(check);
}
