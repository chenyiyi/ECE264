
#include <string.h>

#include "answer09.h"
/*int main(int argc, char* argv[])
{
  //BusinessNode * tr;
  //BusinessNode * br;
  BusinessNode * cr;
  printf("1\n");
    char * stars = strdup("3.0");
    char * name = strdup("sb");
    char * address= strdup("no address");
    char * stars1 = strdup("4.0");
    char * name1 = strdup("sb");
    char * address1= strdup("no addresslllll");
    tr = create_node(stars, name, address);
    br = create_node(stars1, name1, address1);
    tr = tree_insert(br, tr);
    printf("%s\n", tr->left->name);
  cr = load_tree_from_file("yelp_businesses.tsv");
   printf("%s\n", cr->name);  
  return EXIT_SUCCESS;
}*/



BusinessNode * create_node(char * stars, char * name, char * address)
{
  BusinessNode * tn;
  tn = malloc(sizeof(BusinessNode));
  tn -> left = NULL;
  tn -> right = NULL;
  tn -> name = name;
  tn -> stars = stars;
  tn -> address = address;
	
  return (tn);
}

BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
  if (root == NULL )
    {
      return node;
    }
  if (strcmp(root -> name, node -> name) == 0 )
    {
      root -> left = tree_insert (node, root -> left);
    }
  else if ( strcmp(root -> name, node -> name) > 0 )
    {
      root -> left = tree_insert (node, root -> left);
    }
  else
    {
      root -> right = tree_insert (node, root -> right);
    }
  return root;
}

BusinessNode * load_tree_from_file(char * filename)
{
  FILE * fptr;
  fptr = fopen(filename, "r");
  printf("File name is %s\n", filename);
  if(!fptr)
  {
    return NULL;
  }
  BusinessNode * root = NULL;
  BusinessNode * node = NULL;
  char *buffer = malloc(sizeof(char)* 2000);
  int i = 0;
  int d = 0;
  int f = 0;
  while(fgets(buffer, 300, fptr)!=NULL)
    {
      i = 0;
      d = 0;
      while(buffer[d] != '\t' )
	{
	  d ++;
	}
      char* stars = malloc(sizeof(char) * (d+1));
      d =0;
      while(buffer[d] != '\t' )
	{
	  stars[i] = buffer[d];
	  i ++;
	  d ++;
	}
      stars[i] = '\0';
      d++;
      while(buffer[d] != '\t' )
	{
	  d ++;
	}
      char* name = malloc(sizeof(char) * (d-i+1));
      d =i+1;
      i =0;
      while(buffer[d] != '\t' )
	{
	  name[i] = buffer[d];
	  i ++;
	  d ++;
	}
      name[i] ='\0';
      d++;
      f = d;
      while(buffer[d] != '\n' )
	{
	  d ++;
	}
      char* address = malloc(sizeof(char) * (d-f+1));
      d =f;
      i =0;
      while(buffer[d] != '\n' )
	{
	  address[i] = buffer[d];
	  i ++;
	  d ++;
	}
      address[i] = '\0';
      node = create_node(stars, name, address);
      root = tree_insert(node, root);
    } 
  free(buffer);
  fclose(fptr);
  return root;		
}

BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
  if (root == NULL )
    {
      return NULL ;
    }
  if (strcmp (name, root ->name) ==0)
    {
      return root;
    }
  if ( strcmp (name, root ->name) <0)
    {
      return tree_search_name (name, root->left );
    }
  return tree_search_name (name, root->right);
}

void destroy_tree(BusinessNode * root)
{
  if(root == NULL)
    {
      return;
    }
  destroy_tree(root -> left);
  destroy_tree(root -> right);
  free(root ->name);
  free(root ->stars);
  free(root ->address);
  free(root);
	
}









