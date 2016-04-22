#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"answer05.h"
void partitionAllin(int *buffer, int num, int ind);
void partitionIncreasingin(int *buffer, int num, int ind, int small);
void partitionDecreasingin(int *buffer, int num, int ind, int big);
void partitionEvenin(int *buffer, int num, int ind);
void partitionOddin(int *buffer, int num, int ind);
void partitionOddAndEvenin(int *buffer, int num, int ind, int status);
void partitionPrimein(int *buffer, int num, int ind);
int checkprime(int val);

void partitionAll (int value)
{
  int * buffer;
  int ind;
 
  buffer = malloc(sizeof(int) * value);
  ind=0;
  partitionAllin(buffer, value, ind);
  free(buffer);
  
}

void partitionAllin(int *buffer, int num, int ind)
{
  int i;
  int h;
  if(num == 0)
    {
	  printf("= ");
      for(h=0; h<ind-1; h++)
	{
	  printf("%d + ", buffer[h]);
	}
      printf("%d\n", buffer[h]);
      return;
      
    }
  for(i=1; i<=num; i++)
    {
      buffer[ind] = i;
      partitionAllin(buffer, num-i, ind+1);
    }
}

void partitionIncreasing(int value)
{
  int * buffer;
  int ind;
  int small = 1;	
 
  buffer = malloc(sizeof(int) * value);
  ind=0;
  partitionIncreasingin(buffer, value, ind, small);
  free(buffer);
  
}

void partitionIncreasingin(int *buffer, int num, int ind, int small)
{
  int i;
  int h;
  if(num == 0)
    {
	  printf("= ");
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
      partitionIncreasingin(buffer, num-i, ind+1, i+1);
    }
}

void partitionDecreasing (int value)
{
  int * buffer;
  int ind;
  int big;
  
  buffer = malloc(sizeof(int) * value);
  ind=0;
  big = value;
  partitionDecreasingin(buffer, value, ind, big);
  free(buffer);
  
}
  
void partitionDecreasingin(int *buffer, int num, int ind, int big)
{
  int i;
  int h;
  if(num == 0)
    {
      printf("= ");
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

void partitionEven (int value)
{
  int * buffer;
  int ind;
 
  buffer = malloc(sizeof(int) * value);
  ind=0;
  partitionEvenin(buffer, value, ind);
  free(buffer);
  
}
		 
void partitionEvenin(int *buffer, int num, int ind)
{
  int i;
  int h;
  if(num == 0)
    {
	  printf("= ");
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

void partitionOdd (int value)
{
  int * buffer;
  int ind;
 
  buffer = malloc(sizeof(int) * value);
  ind=0;
  partitionOddin(buffer, value, ind);
  free(buffer);
	
}

void partitionOddin(int *buffer, int num, int ind)
{
  int i;
  int h;
  if(num == 0)
    {
	  printf("= ");
      for(h=0; h<ind-1; h++)
	{
	  printf("%d + ", buffer[h]);
	}
      printf("%d\n", buffer[h]);
      return;

    }
  for(i=1; i<=num; i=i+2)
    {
      buffer[ind] = i;
      partitionOddin(buffer, num-i, ind+1);  
    }

} 

void partitionOddAndEven (int value)
{
  int * buffer;
  int ind;
  int status;
 
  buffer = malloc(sizeof(int) * value);
  ind=0;
  status = 2;
  partitionOddAndEvenin(buffer, value, ind, status);
  free(buffer); 
  
}

void partitionOddAndEvenin(int *buffer, int num, int ind, int status)
{
  int i;
  int h;
  int choice;
  int statusNew;
  if(num == 0)
    {
	  printf("= ");
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

void partitionPrime (int value)
{
  int * buffer;
  int ind;
 
  buffer = malloc(sizeof(int) * value);
  ind=0;
  partitionPrimein(buffer, value, ind);
  free(buffer);
  
}

void partitionPrimein(int *buffer, int num, int ind)
{
  int i;
  int h;
  int check;
  if(num == 0)
    {
	  printf("= ");
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

