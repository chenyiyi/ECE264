#include "answer06.h"
#include <stdio.h>
#include <stdlib.h>
void check(int row, int col, char direction, int distance, char** maze, int w, int h);

void print_directions(char** maze, int w, int h) 
{
  int distance;
  char direction;
  char ch;
  int row;
  int col;
  row = 0;
  col = 0;
  while(col < w)
    {
      ch = maze[row][col];
      if(ch == ' ')
	{
	  row++;
	  break;
	}
      col++;
    }
  distance = 0;
  direction = 'Y';
  maze[row-1][col] = 'X';
  printf("%c %d\n", 'S', 1);
  check(row, col, direction, distance, maze, w, h);
	
}


void check(int row, int col, char direction, int distance, char** maze, int w, int h)
{
  char ch;
  char direc;
  int dis;
  int number=0;
  int print =0;
  dis = 1;
  if(row!=0 && direction != 'S')
    {
      ch = maze[row-1][col];
      if(ch ==' ')
	{
	  direc = 'N';
	  if(direc == direction)
	    {
	      check(row-1, col, direc, distance+1, maze, w, h);
	    }
	  else
	    {
	      if(direction!='Y')
		{
		  printf("%c %d\n", direction, distance);
		}
	      check(row-1, col, direc, dis, maze, w, h);
	      print =1;
	    }
	  number=1;
	}
    }
  if(col!=0 && direction != 'E')
    {
      ch = maze[row][col-1];
      if(ch ==' ')
	{
	  direc = 'W';
	  if(direc == direction)
	    {
	      if(print==1)
		{
		  check(row, col-1, direc, 1, maze, w, h);
		}
	      else
		{
		  check(row, col-1, direc, distance+1, maze, w, h);
		}
	    }
	  else
	    {
	      if(direction!='Y' && (number ==0 || print ==0))
		{
		  printf("%c %d\n", direction, distance);
		}
	      check(row, col-1, direc, dis, maze, w, h);
	      print =1;
	    }
	  number=1;
	}
    }
  if(row<(h-1) && direction != 'N')
    {
      ch = maze[row+1][col];
      if(ch ==' ')
	{
	  direc = 'S';
	  if(direc == direction)
	    {
	      if(print ==1)
		{
		  check(row+1, col, direc, 1, maze, w, h);
		}
	      else
		{
		  check(row+1, col, direc, distance+1, maze, w, h);
		}
	    }
	  else
	    {
	      if((direction!='Y') && (number ==0 ||print==0))
		{
		  printf("%c %d\n", direction, distance);
		}
	      check(row+1, col, direc, dis, maze, w, h);
	      print =1;
	    }
	  number=1;
	}
    }
  if(col<(w-1) && direction != 'W')
    {
      ch = maze[row][col+1];
      if(ch ==' ')
	{
	  direc = 'E';
	  if(direc == direction)
	    {
	      if(print==1)
		{
		 check(row, col+1, direc, 1, maze, w, h);
		}
	      else
		{
		  check(row, col+1, direc, distance+1, maze, w, h);
		}
	    }
	  else
	    {
	      if((direction!='Y') && (number ==0 || print ==0))
		{
		  if(row!=(h-2) || (maze[row+1][col] != ' '))
		    {
		      printf("%c %d\n", direction, distance);
		    }
		}
	      check(row, col+1, direc, dis, maze, w, h);
	      print =1;
	    }
	  number=1;
	}
    }
  if(number==0) 
    {
      printf("%c %d\n", direction, distance);
    }
  if((number ==0 || print ==1)&& (row!=(h-1) && col !=(w-1) && row!=0 && col !=0))
    {
      if(direction=='W')
	{
	  printf("%c %d\n", 'E', distance);
	}
      else if(direction=='S')
	{
	  printf("%c %d\n", 'N', distance);
	}		
      else if(direction=='N')
	{
	  printf("%c %d\n", 'S', distance);
	}		
      else if(direction=='E')
	{
	  printf("%c %d\n", 'W', distance);
	}
    }
  else if(row==(h-1))
    {
      printf("%c %d\n", 'N',1 );
    }
  else if(row==0)
    {
      printf("%c %d\n", 'S',1 );
    }
  else if(col==0)
    {
      printf("%c %d\n", 'W',1 );
    }
  else if(col==(w-1))
    {
      printf("%c %d\n", 'E',1 );
    }
      

  return;

}			
			
			
			
			
			
			
