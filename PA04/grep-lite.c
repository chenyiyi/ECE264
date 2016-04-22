#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH 2000
int main(int argc, char *argv[])
{
  int num;
  int counter = 0;
  int match = 0;
  int line = 0;
  int quiet = 0;
  int selectnum = 0;
  char str[MAX_LENGTH];
  for(num=1; num<argc; num++)
    {
      if(strcmp(argv[num],"--help")==0)
	{
	  printf("Usage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n  -v, --invert-match     print non-matching lines\n  -n, --line-number      print line numbers with output\n  -q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.\n");
	  return 0;
	}
    }

  for(num=1; num<argc-1; num++)
    {
      if((strcmp(argv[num],"--invert-match")==0) || (strcmp(argv[num],"-v")==0))
	{
	  match = 1;
	}
      else if((strcmp(argv[num],"--line-number")==0) || (strcmp(argv[num],"-n")==0))
	{
	  line =1;
	}
      else if((strcmp(argv[num],"--quiet")==0) || (strcmp(argv[num],"-q")==0))
	{
	  quiet =1;
	}
      else 
	{
	  fprintf(stderr,"Error input.\n");
	}
    }

  if(*argv[argc-1] == '-')
    {
      fprintf(stderr,"Pattern can not begin with -\n");
      return 2;
    }
  

  while(!feof(stdin))
    {
	  while(fgets(str, MAX_LENGTH, stdin)!=NULL)
	    {
	      counter++;
	      if(strstr(str,argv[argc-1])==NULL && (match==1) && (quiet==0))
		{
		  if(line==0)
		    {
		      printf("%s", str);
		    }
		  else if(line==1)
		    {
		      printf("%d:", counter);
		      printf("%s", str);
		    }
		}
	      else if(strstr(str,argv[argc-1])!=NULL && (match == 0))
		{
		  if(quiet ==0)
		    {
		      if(line ==1)
			{
			  printf("%d:", counter);
			  printf("%s", str);
			  selectnum =1;
			}
		      else if(line==0)
			{
			  printf("%s", str);
			  selectnum =1;
			}
		    }
		  else if(quiet==1)
		    {
		      selectnum =1;
		    }
		}
	      else if(strstr(str,argv[argc-1])!=NULL && (match == 1))
		{
		  selectnum =1;
		}
	    }
    }
  if(selectnum != 0)
    {
      return 0;
    }
  else
    {
      return 1;
    }
 
}

