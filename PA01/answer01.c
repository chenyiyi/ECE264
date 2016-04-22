#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
  int ind;
  int sum = 0;
  for (ind = 0; ind < len; ind ++)
    {
      sum += array[ind];
    }
  return sum;
}
 
int arrayCountNegative(int * array, int len)
{
  int count = 0;
  int ind;
  if (len == 0)
    {
      count = 0;
    }
  else
    {
      for (ind = 0; ind < len; ind++)
	{
	  if(array[ind] < 0)
	    {
	      count++;
	    }
	}
    }
      return count;
}

int arrayIsIncreasing(int * array, int len)
{
  int ind;
  int isInc = 1;
  if(len == 1 ||0)
    {
      isInc = 1;
    }
  else
    {
      for (ind = 1; ind < len; ind++)
	{
	  if(array[ind-1] > array[ind])
	    {
	      isInc = 0;
	      ind = len;
	    }
	}
    }
    return isInc;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
  int ind;
  int needleIndex = -1;
  for (ind = 0; ind < len; ind++)
    {
      if(haystack[ind] == needle)
	{
	  needleIndex = ind;
	}
    }
    return needleIndex;
}

int arrayFindSmallest(int * array, int len)
{
  int smallest = array[0];
  int indSmallest = 0;
  int ind;
  if (len == 0)
    {
      indSmallest = 0;
    }
  else
    {
      for (ind =1; ind < len; ind++)
	{
	  if(array[ind] < smallest)
	    {
	      smallest = array[ind];
	      indSmallest = ind;
	    }
	}
    }
    return indSmallest;
}
