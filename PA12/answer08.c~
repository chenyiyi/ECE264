#include "answer08.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
typedef struct{
  uint128 s;
  uint128 e;
  uint128 value;
  int * ptr;
}ParamBlock;

ParamBlock * ParamBlock_create(uint128 s, uint128 e, int * ptr, uint128 value);
void * thread_worker(void * paramblock);
void ParamBlock_destroy(ParamBlock * p);


uint128 alphaTou128(const char * str)
{
  uint128 ret = 0;
  int ind = 0;
  while(str[ind] < 48 || str[ind] > 57){
    if(str[ind] == '-')
      return 0;
    ind++;
  }
  while(str[ind] >= 48 && str[ind] <= 57){
    ret = 10 * ret + str[ind] - 48;
    ind++;
  }
  return ret;
}
char * u128ToString(uint128 value)
{
  uint128 tmp = value;
  int ind = 0;
  if(tmp == 0){
    char * ret1 = strdup("0");
    return ret1;
  }
  while (tmp!= 0){
    tmp = tmp / 10;
    ind++;
  }
  char * ret = malloc((ind + 1) * sizeof(char));
  ret[ind] = 0;
  ind -= 1;
  while(ind >= 0){
    ret[ind] = value % 10 + 48;
    value /= 10;
    ind--;
  }
  return ret;
}
int primalityTestParallel(uint128 value, int n_threads)
{
  ParamBlock * * ps = malloc(sizeof(ParamBlock *) * n_threads);
  long * status = malloc(sizeof(long) * n_threads);
  pthread_t * th = malloc(sizeof(pthread_t) * n_threads);
  int ret = 0;
  uint128 ind;
  uint128 max = floor(sqrt(value) * 1.10);
  uint128 bin = max / n_threads;

  for(ind = 0; ind < n_threads - 1; ind++)
    ps[ind] = ParamBlock_create(ind * bin, (ind + 1) * bin, &ret,value);
  ps[ind] = ParamBlock_create(ind * bin, max, &ret,value);
  if(value == 2)
    ret = 0;
  else if(value % 2 == 0)
    ret = 1;
  else{
  for(ind = 0; ind < n_threads; ++ind){
    int created = pthread_create(&th[ind], NULL,
				 (void * (*)(void*)) thread_worker,
				 (void*) ps[ind]);
    if(created != 0)
      fprintf(stderr, "Failed to create thread!\n");
  }

  for(ind = 0; ind < n_threads; ind++)
    pthread_join(th[ind], (void *) &status[ind]);
  }
  free(th);
  free(status);
  for(ind = 0; ind < n_threads; ind++)
    ParamBlock_destroy(ps[ind]);
  free(ps);
  return !ret;
}
void * thread_worker(void * paramblock)
{
  ParamBlock * p = (ParamBlock *) paramblock;
  if(p->s < 3)
    p->s = 3;
  if(p->s % 2 == 0)
    p->s += 1;
  if((p->s > p->e) || (p->s > p->value))
    pthread_exit(0);
  uint128 i;
  for (i = p->s; i <= p->e && *(p->ptr) == 0; i+=2) 
    {
      if((p->value % i) == 0) 
	*(p->ptr) = 1;
    }	

  pthread_exit(0);

}
ParamBlock * ParamBlock_create(uint128 s, uint128 e, int * ptr, uint128 value)
{
  ParamBlock * ret = malloc(sizeof(ParamBlock));
  ret->s = s;
  ret->e = e;
  ret->ptr = ptr;
  ret->value = value;
  return ret;
}
void ParamBlock_destroy(ParamBlock * p)
{
  free(p);
}
