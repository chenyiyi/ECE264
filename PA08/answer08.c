#include "answer08.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

List * List_createNode(const char * str)
{
  List * nd = malloc(sizeof(List));
  nd -> str = strdup(str);
  nd -> next = NULL;
  
  return (nd);
}

void List_destroy(List * list)
{
  if(list != NULL)
    {
      if(list->next != NULL)
	{
	  while(list ->next != NULL){
	    List * node = list -> next;
	    free(list ->str);
	    free(list);
	    list = node;
	  }
	  free(list ->str);
	  free(list);
	}
      else{
	free(list ->str);
	free(list);
      }
    }
}

int List_length(List * list)
{
  int len1 =0 ; 
  List *ptr = list;
  while(ptr != NULL){
    len1 ++;
    ptr = ptr->next;
      }
  return (len1);
}

List * List_merge(List * lhs, List * rhs, int (*compar)(const char *, const char*))
{
  List *write_node;
  List *ptr =NULL;
  if(lhs == NULL){
    write_node = rhs;
  }
  else if(rhs == NULL){
    write_node = lhs;
  }
  else
    {
      if(lhs != NULL && rhs != NULL)
	{
	  int cmp = compar(lhs->str,rhs->str);
	  if(cmp <= 0){
	    write_node = lhs;
	    lhs = lhs->next;
	  }
	  else{
	    write_node = rhs;
	    rhs = rhs->next;
	  }
	   ptr = write_node;
	}
      while(lhs != NULL && rhs != NULL)
	{
	  int cmp = compar(lhs->str,rhs->str);
	  if(cmp <= 0){
	    ptr->next = lhs;
	    lhs = lhs->next;
	  }
	  else{
	    ptr->next = rhs;
	    rhs = rhs->next;
	  }
	  ptr = ptr->next;
	}
      if(lhs != NULL){
	ptr->next = lhs;
      }
      if(rhs != NULL){
	ptr->next = rhs;
      }
    }
  return write_node;
}

List * List_sort(List * list, int (*compar)(const char *, const char*))
{
  int length;
  List * ptr1;
  List * final;
  length = List_length(list);
  int ind =1;
  if(length <=1)
    {
      return(list);
    }
  int leftlength = length/2;
  List *left = list;
  List *right;
  ptr1 = list;
  while(ind <= leftlength-1)
    {
      ptr1 = ptr1 ->next;
      ind ++;
    }
  right = ptr1->next;
  ptr1->next = NULL;
  left = List_sort(left, compar);
  right = List_sort(right, compar);
  final = List_merge(left, right, compar);

  return (final);

}






