#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include "answer09.h"

char * * explode(const char * str, const char * delims)
{
    int n = 0;
    int i = 0;
    int j = 0;
    while(str[i] != '\0')
    {
      if(strchr(delims,str[i]) != NULL){
            n++;
      }
      i++;
    }
    char * * strArr = malloc((n+1) * sizeof(char *));
    size_t arrind = 0;
    size_t last = 0;
    for(i=0;i<=strlen((char*)str);i++)
    {
        if(strchr(delims,str[i]) != NULL)
        {
            char * new_string = (char *)malloc((last+1-arrind) * sizeof(char));
            //strArr[j] = malloc((last+1-arrind) * sizeof(char));
            
            memcpy(new_string,str+arrind,last+1-arrind);
            new_string[last-arrind] = '\0';
            
            //strcpy((char*)strArr,new_string);
            //memcpy((char*)strArr,new_string,last+1-arrind);
            strArr[j] = new_string;
            j++;
            arrind = last+1;
            //free(new_string);
            //strArr++;
        }
        last++;
    }
     // for(i=0;i<=*arrLen;i++)
     // {
     //     free(strArr[i]);
     // }
return(strArr);
//free(strArr);
}

BusinessNode *
create_node(char * stars, char * name, char * address){
	BusinessNode * bs;
	bs = malloc(sizeof(BusinessNode));
	bs->left = NULL;
	bs->right = NULL;
	bs->stars = stars;
	bs->name = name;
	bs->address = address;
	return bs;
}

BusinessNode *
tree_insert(BusinessNode * node, BusinessNode * root){
	if(root == NULL)
	  return node;
	if(strcmp(node->name, root->name) <= 0){
		root->left = tree_insert(node, root->left);
	}
	else{
		root->right = tree_insert(node, root->right);
	}
	return root;
}

BusinessNode *
load_tree_from_file(char * filename){
	char str[2000];
	char * * strArr;
	int i;
	BusinessNode * root = NULL;
	BusinessNode * node = NULL;
	FILE * fp; 
	if((fp = fopen(filename,"r")) == NULL)
		return root;
	while(fgets(str,2000,fp) != NULL){
		strArr = explode(str,"\t");
		node = create_node(strArr[0], strArr[1], strArr[2]);
		root = tree_insert(node, root);
	}
	fclose(fp);
	for(i = 0; i<=2; i++)
		free(strArr[i]);
	free(strArr);
	return root;
}

BusinessNode *
tree_search_name(char * name, BusinessNode * root){
	if(root == NULL)
		return NULL;
	if(strcmp(name, root->name) == 0)
		return root;
	if(strcmp(name, root->name) < 0)
		return tree_search_name(name, root->left);
	return tree_search_name(name, root->right);
}

void
destroy_tree(BusinessNode * root){
	if (root == NULL){
		return;
	}
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root ->name);
	free(root ->stars);
	free(root ->address);
	free(root);
}
