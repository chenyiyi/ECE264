#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
  int num;
  for(num=1; num<argc; num++)
    {
      printf("%s ", argv[num]);
    }
  printf("\n");
  return EXIT_SUCCESS;
}
  
