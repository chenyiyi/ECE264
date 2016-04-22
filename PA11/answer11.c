#include "answer11.h"
#include <stdlib.h>
void Stacknode_destroy(StackNode * stacknode);
unsigned char bit_read(unsigned char *first, int * ind, FILE *fp);
unsigned char byte_read(unsigned char *first, int *ind, FILE *fp);

#define TRUE 1
#define FALSE 0

HuffNode * HuffNode_create(int value)
{
  HuffNode * node = malloc(sizeof(HuffNode));
  node -> value = value;
  node -> left = NULL;
  node -> right = NULL;
  return node;
}

void HuffNode_destroy(HuffNode * tree)
{
  if(tree ==NULL){
    return;
  }
  HuffNode_destroy(tree->left);
  HuffNode_destroy(tree->right);
  free(tree);
}

Stack * Stack_create()
{
  Stack * create_stack = malloc(sizeof(Stack));
  create_stack -> head = NULL;
  return create_stack;
}

void Stack_destroy(Stack * stack)
{
  if(stack == NULL){
    return;
  }
  Stacknode_destroy(stack->head);
  free(stack);
}
	
void Stacknode_destroy(StackNode * stacknode)
{
  if(stacknode == NULL){
    return;
  }
  Stacknode_destroy(stacknode->next);
  HuffNode_destroy(stacknode->tree);
  free(stacknode->next);
}

int Stack_isEmpty(Stack * stack)
{
  if(stack ==NULL){
    return TRUE;
  }
  return FALSE;
}

HuffNode * Stack_popFront(Stack * stack)
{
  if(Stack_isEmpty(stack)){
    return NULL;
  }
  HuffNode * poptree;
  StackNode * popnode;
  poptree = stack->head->tree;
  popnode = stack->head->next;
  free(stack->head);
  stack->head = popnode;
  return poptree;
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
  StackNode * pushnode = malloc(sizeof(StackNode));
  pushnode -> tree = tree;
  pushnode -> next = stack -> head;
  stack->head = pushnode;
}

void Stack_popPopCombinePush(Stack * stack)
{
  HuffNode * popnode1 = Stack_popFront(stack);
  HuffNode * popnode2 = Stack_popFront(stack);
  HuffNode * node_combine = HuffNode_create(0);
  node_combine->left = popnode2;
  node_combine->right = popnode1;
  Stack_pushFront(stack, node_combine);
}

HuffNode * HuffTree_readTextHeader(FILE * fp)
{
  if(fp == NULL){
    fprintf(stderr,"Failed to open\n");
    return NULL;
  }
  Stack * stack = Stack_create();
  int ind = fgetc(fp);
  while(!feof(fp))
    {
      if(ind ==48){
	if(stack->head->next ==NULL){
	  break;
	}
	Stack_popPopCombinePush(stack);
      }
      if(ind ==49){
	ind = fgetc(fp);
	HuffNode * node = HuffNode_create(ind);
	Stack_pushFront(stack, node);
      }
      ind = fgetc(fp);
    }
  HuffNode * final = Stack_popFront(stack);
  Stack_destroy(stack);
  return final;
}
	
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
  if(fp ==NULL){
    fprintf(stderr,"Failed to open\n");
    return NULL;
  }
  Stack * stack = Stack_create();
  unsigned char * first = malloc(sizeof(unsigned char));
  * first = fgetc(fp);
  int * ind = malloc(sizeof(int));
  unsigned char bit; 
  * ind = 7;
  bit = bit_read(first, ind, fp);
  while(!feof(fp)){
    if(bit ==1){
      unsigned char realread = byte_read(first, ind, fp);
      HuffNode * node = HuffNode_create(realread);
      Stack_pushFront(stack, node);
    }
    if(bit ==0){
      if(stack->head->next ==NULL){
	break;
      }
      Stack_popPopCombinePush(stack);
    }
    bit = bit_read(first, ind, fp);
  }
  free(ind);
  free(first);
  HuffNode * final = Stack_popFront(stack);
  Stack_destroy(stack);

  return final;
}

unsigned char bit_read(unsigned char *first, int * ind, FILE *fp)
{
  if(*ind ==-1){
    * first = fgetc(fp);
    * ind = 7;
  }
  unsigned char bit = (*first >> *ind) & 0x01;
  *ind = *ind-1;

  return bit;
}
	
unsigned char byte_read(unsigned char *first, int *ind, FILE *fp)
{
  unsigned char byteread = 0;
  int byteindex;
  for(byteindex =7; byteindex>=0; byteindex--){
    byteread = byteread + (bit_read(first, ind, fp) << byteindex);
  }
  return byteread;
}
	
	
	
	
	
		
		


















