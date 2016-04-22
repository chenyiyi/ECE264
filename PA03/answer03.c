#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "answer03.h"
//#define TEST
#ifdef TEST
int compareA(const void *arrA, const void *arrB);
int compareB(const void *arrA, const void *arrB);

int main(int argc, char * * argv)
{
  char * q = strdup("we are purdue student ha ha ha ha ha");
  sortStringCharacters(q);
  printf("%s",q);
  free(q);
  return EXIT_SUCCESS;
}
#endif

char * strcat_ex(char * * dest, int * n, const char * src)
{
  char * str;
  if((* dest == NULL) || (* n < strlen(* dest) + strlen(src)+1))
    {
      if( *dest ==NULL)
	{
	  * n = 1 + 2 * strlen(src);
	  str = malloc(*n * sizeof(char));
	  str[0] = '\0';
	  strcpy(str, src);
	  *dest = str;
	  return(* dest);
	}
      else
	{
	  * n = 1 + 2 * (strlen(* dest) + strlen(src));
	  str = malloc(sizeof(char) * (*n));
	  str[0] = '\0';
	  strcpy(str, *dest);
	  strcat(str, src);
	  free(* dest);
	  *dest = str;
	  return(* dest);
	}
    }
  else
    {
      strcat(* dest, src);
      return(* dest);
    }
}
      
char * * explode(const char * str, const char * delims, int * arrlen)
{
  int N=0;
  int ind;
  int num;
  int arrInd = 0;
  int last = 0;
  for(ind = 0; str[ind] != '\0'; ind++)
    {
      if (strchr(delims, str[ind]) != NULL)
	{
	  N++;
	}
    }
  char * * strArr = malloc((N+1) * sizeof(char *));
  for(num = 0; str[num] != '\0'; num++)
    {
      if (strchr(delims, str[num]) != NULL)
	{
	  strArr[arrInd] = malloc((num-last+1)* sizeof(char));
	  memcpy(strArr[arrInd], str+last, num-last);
	  *(strArr[arrInd] + num - last) = '\0';
	  last = num +1;
	  arrInd++;
	}
    }
  strArr[arrInd] = malloc((num - last + 1) * sizeof(char));
  memcpy(strArr[arrInd], str+last, num-last);
  *(strArr[arrInd] + num - last) = '\0';
  * arrlen = N+1;

  return strArr;
}

char * implode(char * * strArr, int len, const char * glue)
{
  int num = 1;
  int ind;
  char *str = malloc (((strlen(strArr[0])+1))* sizeof(char));
  memcpy(str, strArr[0], strlen(strArr[0])+1);
  for(ind = 1; ind < len; ind++)
    {
      str = strcat_ex(&str, &num, glue);
      str = strcat_ex(&str, &num, strArr[ind]);
    }
  return str;
}

int compareA(const void *arrA, const void *arrB)
{
  char * *aA = (char * *)arrA;
  char * *aB = (char * *)arrB;
  return(strcmp(*aA, *aB));
}


void sortStringArray(char * * arrString, int len)
{
  qsort(arrString, len, sizeof(char *), compareA);
}

int compareB(const void * arrA, const void * arrB)
{
  char *aA = (char *)arrA;
  char *aB = (char *)arrB;
  return *aA > *aB;
}

void sortStringCharacters(char * str)
{
  qsort(str, strlen(str), sizeof(char), compareB);
}

void destroyStringArray(char * * strArr, int len)
{
  int num;
  for(num =0; num<len; num++)
    {
      free(strArr[num]);
    }
  free(strArr);

}


