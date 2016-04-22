#include "answer12.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
typedef struct{
  uint128 end;
  uint128 value;
  uint128 start;
  int * ind;
}ThreadBlock;

ThreadBlock * ThreadBlock_create(uint128 end, uint128 value, uint128 start,int *ind);
void * thread_help(void * Threadblock);

uint128 alphaTou128(const char * str)
{
  uint128 result=0;
  int ind =0;
  while(str[ind] < 48 || str[ind] >57)
    {
      if(str[ind] =='-'){
	return FALSE;
      }
      ind ++;
    }
  while(str[ind] >= 48 && str[ind] <= 57)
    {
      result = result *10;
      result = result + str[ind] - '0';
      ind ++;
    }
  return result;
}

char * u128ToString(uint128 value)
{
  uint128 val = value;
  int ind = 0;
  if(val ==0){
    char * ret = strdup("0");
    return ret;
  }
  while(val!=0)
    {
      val = val/10;
      ind++;
    }
  char * result = malloc(sizeof(char) *(ind+1));
  result[ind] = 0;
  ind = ind-1;
  while(ind >=0){
    result[ind] = value % 10 +48;
    value = value /10;
    ind--;
  }
  return result;
}

int primalityTestParallel(uint128 value, int n_threads)
{
  ThreadBlock * * tb = malloc(sizeof(ThreadBlock *) *n_threads);
  pthread_t * a = malloc(sizeof(pthread_t) * n_threads);
  long * status = malloc(sizeof(long) * n_threads);
  int ret = 0;
  uint128 ind;
  uint128 max = floor(sqrt(value)* 1.05);
  uint128 bin = max/n_threads;

  for(ind =0; ind<n_threads-1; ind++){
    tb[ind] = ThreadBlock_create((ind+1) * bin, value, ind* bin, &ret);
  }
     tb[ind] = ThreadBlock_create(max, value, ind* bin, &ret);
  if(value ==2){
    ret =0;
  }
  else if(value %2 ==0)
    {
      ret =1;
    }
  else{
    for(ind =0; ind<n_threads; ind++){
      int thread = pthread_create(&a[ind],NULL, (void * (*)(void*))thread_help, (void*) tb[ind]);
      if(thread !=0){
	fprintf(stderr, "Failed to create thread.\n");
      }
    }
  for(ind =0; ind <n_threads; ind++)
    {
      pthread_join(a[ind], (void *) &status[ind]);
    }
  }
  free(a);
  free(status);
  for(ind = 0; ind <n_threads; ind++)
    {
      free(tb[ind]);
    }
  free(tb);
  return !ret;
}

void * thread_help(void * Threadblock)
{
  ThreadBlock * h = (ThreadBlock *) Threadblock;
  if(h->start < 3){
    h->start = 3;
  }
  if(h->start % 2==0)
    {
      h->start +=1;
    }
  if((h->start > h ->end) || (h->start > h->value)){
    pthread_exit(0);
  }
  uint128 b;
  for (b = h->start; b <= h->end && *(h->ind) ==0; b= b+2)
    {
      if((h->value %b) ==0){
	*(h->ind) =1;
      }
    }
  pthread_exit(0);
}

ThreadBlock * ThreadBlock_create(uint128 end, uint128 value, uint128 start, int * ind)
{
  ThreadBlock * result = malloc(sizeof(ThreadBlock));
  result->start = start;
  result->end = end;
  result->ind = ind;
  result->value = value;
  return result;
}


