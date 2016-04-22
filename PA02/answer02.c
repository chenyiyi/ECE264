#include <stdio.h>
#include "answer02.h"
//#define TEST
#ifdef TEST
int main(int argc, char * * argv)
{
  printf("%d\n", my_atoi("0"));

  return EXIT_SUCCESS;
}
#endif
size_t my_strlen(const char * str)
{
  int num=0;
  while(str[num] != '\0')
    {
      num++;
    }
  
  return(num);
}


int my_countchar(const char * str, char ch)
{
  int num=0;
  int indexc;
  for (indexc= 0; str[indexc] != '\0'; indexc++)
    {
      if(str[indexc] == ch)
	{
	  num++;
	}
    }

  return(num);
}

char * my_strchr(const char * str, int ch)
{
  int index=0;
  int length;
  length = my_strlen(str);
  while (str[index]!=ch && index<=length)
    {
      index++;
    }
  if (length<index)
    {
      return(NULL);
    }
  else
    {
      return (char *) &str[index];
    }
}

char * my_strrchr(const char * str, int ch)
{
  int index=0;
  int length;
  length = my_strlen(str);
  while (str[length - index]!=ch && index<=length)
    {
      index++;
    }
  if (length<index)
    {
      return(NULL);
    }
  else
    {
      length = length - index;
      return (char *) &str[length];
    }
}

char * my_strstr(const char * haystack, const char * needle)
{
  int indexh;
  int lengthhay;
  int lengthn;
  int indexn=0;
  lengthn = my_strlen(needle);
  lengthhay = my_strlen(haystack);
  if(needle[0]=='\0')
    {
      return(char *)(haystack);
    }
  else
    {
      for(indexh=0; indexh < (lengthhay); indexh++)
	{
	  while(haystack[indexh]==needle[indexn] && indexn<(lengthn))
	    {
	      indexh++;
	      indexn++;
	    }
	  if(needle[indexn]=='\0')
	    {
	      indexh=indexh-lengthn;
	      break;
	    }
	  else if(indexn<lengthn && indexn>0)
	    {
	      indexh = indexh - 1;
	      indexn = 0;
	    }
	  else
	    {
	      indexn = 0;
	    }
	}
      if(needle[indexn]=='\0')
	{
	  return (char* ) &haystack[indexh];
	}
      else
	{
	  return(NULL);
	}
    }
}

char * my_strcpy(char * dest, const char * src)
{
  int lengthsrc;
  int num;

  lengthsrc = my_strlen(src)+1;
  for (num=0; num<lengthsrc; num++)
    {
      dest[num] = src[num];
    }

  return(dest);
}


char * my_strcat(char * dest, const char * src)
{
  int lengthdest;
  int lengthsrc;
  int index;
  lengthdest = my_strlen(dest);
  lengthsrc = my_strlen(src);
  for(index=0; index <= (lengthsrc-1); index++)
    {
      dest[lengthdest + index] = src[index];
    }
  dest[lengthdest + lengthsrc] = '\0';

  return(dest);

}

int my_isspace(int ch)
{
  if(ch == ' ' || ch=='\f' || ch=='\n' || ch=='\r' || ch=='\t' || ch=='\v')
    {
      return(1);
    }
  else
    {
      return(0);
    }
 }

int my_atoi(const char * str)
{
  int length;
  int index=0;
  int ret;
  int minus = 0;
  int find = 0;
  length = my_strlen(str);
  for(index=0; index<length && !find; index++)
    {
      while(my_isspace(str[index])==1)
	{
	  index++;
	}
      ret = 0;
      while((str[index]<='9') && (str[index]>='0'))
	{
	  if(index != 0 && str[index-1]=='-')
	    {
	      minus = 1;
	    }
	  ret = ret * 10;
	  ret = ret + str[index] - '0';
	  index++;
	  find = 1;
	}
 
    }
  if(minus==1)
    {
      return(-ret);
    }
  else
    {
      return(ret);
    }
}
