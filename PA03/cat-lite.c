#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char * argv[])
{
  FILE * fptr;
  int num;
  char ch;
  for(num=1; num<argc; num++)
    {
      if(strcmp(argv[num],"--help")==0)
	{
	  printf("Usage: cat-lite [--help] [FILE]...\nWith no FILE, or when FILE is -, read standard input.\n\nExamples:\n  cat-lite README   Print the file README to standard output.\n  cat-lite f - g    Print f's contents, then standard input, \n                    then g's contents.\n  cat-lite          Copy standard input to standard output.\n");
	  return EXIT_SUCCESS;
	}
    }
  for(num=1; num<argc; num++)
    {
      if((*argv[num]=='-')|| (*argv[num]=='\0'))
	{
	  fptr = stdin;
	}
      else
	{
	  fptr = fopen(argv[num], "r");
	  if(fptr == NULL)
	    {
	      printf("Cat cannot open %s\n", argv[num]);
	      return EXIT_FAILURE;
	    }
	  else
	    {
	      while(! feof(fptr))
		{
		  ch = fgetc(fptr);
		  printf("%c",ch);
		}
	    }
	}
    }	
  fclose(fptr);
  return EXIT_SUCCESS;
}