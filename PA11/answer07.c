#include "answer11.h"
#include <stdlib.h>
void Stacknode_destroy(StackNode * stacknode);
unsigned char Readbit(unsigned char * byte, int * offset, FILE * fp);
unsigned char Readbyte(unsigned char * byte, int * offset, FILE * fp); 

#define TRUE 1
#define FALSE 0

HuffNode * HuffNode_create(int value)
{
  HuffNode * node = malloc(sizeof(HuffNode));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void HuffNode_destroy(HuffNode * tree)
{
  if(tree == NULL)
    return;
  HuffNode_destroy(tree->left);
  HuffNode_destroy(tree->right);
  free(tree);
}
Stack * Stack_create()
{
  Stack * stack = malloc(sizeof(stack));
  stack->head = NULL;
  return stack;
}
void Stack_destroy(Stack * stack)
{
  if(stack == NULL)
    return;
  Stacknode_destroy(stack->head);
  free(stack);
}
void Stacknode_destroy(StackNode * stacknode)
{
  if(stacknode == NULL)
    return;
  Stacknode_destroy(stacknode->next);
  HuffNode_destroy(stacknode->tree);
  free(stacknode->next);

}
int Stack_isEmpty(Stack * stack)
{
  if(stack == NULL)
    return TRUE;
  return FALSE;
}
HuffNode * Stack_popFront(Stack * stack)
{
  if(Stack_isEmpty(stack))
    return NULL;
  HuffNode * tree = stack->head->tree;
  StackNode * node = stack->head->next;
  free(stack->head);
  stack->head = node;
  return tree;
}
void Stack_pushFront(Stack * stack, HuffNode * tree)
{
  StackNode * stacknode = malloc(sizeof(StackNode));
  stacknode->tree = tree;
  stacknode->next = stack->head; 
  stack->head = stacknode;
}
void Stack_popPopCombinePush(Stack * stack)
{
  HuffNode * node1 = Stack_popFront(stack);
  HuffNode * node2 = Stack_popFront(stack);
  HuffNode * node_new = HuffNode_create(0);
  node_new->left = node2;
  node_new->right = node1;
  Stack_pushFront(stack, node_new);
}
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
  if(fp == NULL){
    fprintf(stderr,"Invalid file pointer\n");
    return NULL;
  }
  Stack * stack = Stack_create();
  int s = fgetc(fp);
  while(!feof(fp)){
    if(s == 48){
      if(stack->head->next == NULL)
	break;
      Stack_popPopCombinePush(stack);
    }
    if(s == 49){
      s = fgetc(fp);
      HuffNode * tree = HuffNode_create(s);
      Stack_pushFront(stack, tree);
    }
    s = fgetc(fp);
  }
  HuffNode * ret = Stack_popFront(stack);
  Stack_destroy(stack);
  return ret;
}
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
  if(fp == NULL){
    fprintf(stderr,"Invalid file pointer\n");
    return NULL;
  }
  Stack * stack = Stack_create();
  unsigned char * byte = malloc(sizeof(unsigned char));
  *byte = fgetc(fp);
  int * offset = malloc(sizeof(int));
  *offset = 7;
  unsigned char bit = Readbit(byte, offset, fp);
  while(!feof(fp)){
    if(bit == 1){
      unsigned char s = Readbyte(byte, offset, fp);
      HuffNode * tree = HuffNode_create(s);
      Stack_pushFront(stack, tree);
    }
    if(bit == 0){
     if(stack->head->next == NULL)
       break;
     Stack_popPopCombinePush(stack);
    }
    bit = Readbit(byte, offset, fp);
  }
  free(byte);
  free(offset);
  HuffNode * ret = Stack_popFront(stack);
  Stack_destroy(stack);
  return ret;
}
unsigned char Readbit(unsigned char * byte, int * offset, FILE * fp)
{
  if(*offset == -1){
    *byte = fgetc(fp);
    *offset = 7;
  }
  unsigned char ret = (*byte>>*offset) & 0x01;
  *offset -= 1;
  return ret;
}
unsigned char Readbyte(unsigned char * byte, int * offset, FILE * fp)
{
  int ind;
  unsigned char ret = 0;
  for(ind = 7; ind >=0; ind--){
    ret += Readbit(byte, offset, fp)<<ind;
  }
  return ret;
}
