#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"
struct rev_self{
	long int offset;
	struct rev_self *left;
	struct rev_self *right;
};

struct loc_self{
	long int offset;
	struct rev_self *rev_loc;
	struct loc_self *left;
	struct loc_self *right;
};

struct bus_self{
	char * name;
	struct loc_self *loc_bus;
	struct bus_self *left;
	struct bus_self *right;
};

struct YelpDataBST{
  struct bus_self * bus_yelp;
};

//const char businesses_path[] = "/home/shay/a/ece264p0/share/yelp_data/businesses.tsv";
//const char reviews_path[] = "/home/shay/a/ece264p0/share/yelp_data/reviews.tsv";
struct bus_self *create_bus(char ** stararr, struct loc_self *loc_root);
struct bus_self *insert_bus(struct bus_self * root, struct bus_self * node);
struct loc_self *create_loc(long int offset, struct rev_self *review_root);
struct loc_self *insert_loc(struct loc_self * root, struct loc_self * node);
struct rev_self *create_rev(long int offset);
struct rev_self * insert_rev(struct rev_self * root, struct rev_self * node);
void search_location(struct loc_self* location, char* state, char* zip_code, struct Location* location_give, struct Review* review, int* rev_index, int* loc_index);
void search_review(struct rev_self* review, struct Review* review_array, int *rev_index);
char * * explode(const char * str, const char * delims);

struct YelpDataBST* create_business_bst(const char* businesses_path,
                                        const char* reviews_path)
{
  FILE * fptrloc = fopen(businesses_path, "r");
  FILE * fptrrev = fopen(reviews_path,"r");
  struct bus_self * bus_root =NULL;
  struct loc_self * loc_root = NULL;
  struct rev_self * review_root = NULL;
  if(fptrloc ==NULL || fptrrev ==NULL){
	fprintf(stderr, "Failed to open file.\n");
	return NULL;
	}
  char* bufferloc = malloc(sizeof(char) * 6000);
  char* bufferreview = malloc(sizeof(char) * 6000);
  long int offset1 = ftell(fptrloc);
  while(fgets(bufferloc, 6000, fptrloc) != NULL)
  {
	char ** stararr1 = explode(bufferloc, "\t\n");
	long int offset2 = ftell(fptrrev);
	fgets(bufferreview, 6000, fptrrev);
	char ** stararr2 = explode(bufferreview, "\t\n");
	while(stararr2[0] == stararr1[0])
	{
		struct rev_self * review = create_rev(offset2);
		review_root = insert_rev(review_root, review);
		offset2 = ftell(fptrrev);
		fgets(bufferreview, 2000, fptrrev);
		stararr2 = explode(bufferreview, "\t\n");
	}
	fseek(fptrrev, offset2, SEEK_SET );
	struct loc_self * loc_node = create_loc(offset1, review_root);
	loc_root = insert_loc(loc_root, loc_node);
	struct bus_self * bus_node = create_bus(stararr1, loc_root);
	bus_root = insert_bus(bus_root, bus_node);
	}
	struct YelpDataBST * Bus_tree;
	Bus_tree->bus_yelp = bus_root;
	
	return Bus_tree;
}
	

struct bus_self *create_bus(char ** stararr, struct loc_self *loc_root){
  struct bus_self * busi = malloc(sizeof (struct bus_self));
  busi->name = stararr[1];
  busi->left = NULL;
  busi->right = NULL;
  busi->loc_bus = loc_root;
  return busi;
}

struct bus_self *insert_bus(struct bus_self * root, struct bus_self * node){
  if(root == NULL){
    return node;
  }
  if(strcasecmp(root->name, node->name) < 0){
    root->left = insert_bus(root->left, node);	
  }
  else if(strcasecmp(root->name, node->name) > 0){
    root->right = insert_bus(root->right, node);
  }
  else{
    struct loc_self *new_loc = malloc(sizeof(struct loc_self));
    new_loc  =insert_loc(root->loc_bus, node->loc_bus);
    root->loc_bus = new_loc;
  }
  return root;
}

struct loc_self *create_loc(long int offset, struct rev_self *review_root){
  struct loc_self * loca = malloc(sizeof(struct loc_self));
  loca->left = NULL;
  loca->right = NULL;
  loca->offset = offset;
  loca->rev_loc = review_root;
  return  loca;
}

struct loc_self *insert_loc(struct loc_self * root, struct loc_self * node){
	if(root == NULL){
		return node;
	}
	FILE * fptr = fopen(businesses_path,"r");
	char* bufferroot = malloc(sizeof(char) * 6000);
	fseek(fptr, root-> offset, SEEK_SET );
	fgets(bufferroot, 6000, fptr);
	char ** strroot = explode(bufferroot, "\t\n");
	char* buffernode = malloc(sizeof(char) * 6000);
	fseek(fptr, node-> offset, SEEK_SET );
	fgets(buffernode, 6000, fptr);
	char ** strnode= explode(buffernode, "\t\n");
	if(strcmp(strroot[4], strnode[4]) < 0){
		root = insert_loc(root->left, node);	
	}
	else if(strcmp(strroot[4], strnode[4]) > 0){
		root = insert_loc(root->right, node);
	}
	else{
		if(strcmp(strroot[3], strnode[3]) < 0){
			root = insert_loc(root->left, node);	
		}
		else if(strcmp(strroot[3], strnode[3]) > 0){
			root = insert_loc(root->right, node);
			}
		else{
			if(strcmp(strroot[2], strnode[2]) < 0){
				root = insert_loc(root->left, node);	
			}
			else if(strcmp(strroot[2], strnode[2]) > 0){
				root = insert_loc(root->right, node);
			}
		}
		}
	return root;
}

struct rev_self *create_rev(long int offset){
  struct rev_self * revi = malloc(sizeof(struct rev_self));
  revi->left = NULL;
  revi->right = NULL;
  revi->offset = offset;
  return revi;
}

struct rev_self * insert_rev(struct rev_self * root, struct rev_self * node){
	if(root == NULL){
	  return node;
	}
	FILE * fptr = fopen(reviews_path,"r");
	char* bufferroot = malloc(sizeof(char) * 6000);
	fseek(fptr, root-> offset, SEEK_SET );
	fgets(bufferroot, 6000, fptr);
	char ** strroot = explode(bufferroot, "\t\n");
	char* buffernode = malloc(sizeof(char) * 6000);
	fseek(fptr, node-> offset, SEEK_SET );
	fgets(buffernode, 6000, fptr);
	char ** strnode= explode(buffernode, "\t\n");
	if(strcmp(strroot[1], strnode[1]) < 0){
		root = insert_rev(root->left, node);	
	}
	else if(strcmp(strroot[1], strnode[1]) > 0){
		root = insert_rev(root->right, node);
	}
	else{
		if(strcmp(strroot[5], strnode[5]) < 0){
			root = insert_rev(root->left, node);	
		}
		else{
			root = insert_rev(root->right, node);
			}
	}
	return root;
}

struct Business* get_business_reviews(struct YelpDataBST* bst,
                                      char* name, char* state, char* zip_code)
{
	if(bst == NULL){
		return NULL;
		}
	struct Business* bus_final = malloc(sizeof(struct Business));
	if(strcasecmp(name, bst->bus_yelp->name) == 0){
		struct Review * review_final = malloc(sizeof(struct Review)* 6000);
		struct Location * location_final = malloc(sizeof(struct Location)*6000);
		int * rev_index = 0;
		int * loc_index = 0;
		search_location(bst->bus_yelp->loc_bus, state, zip_code, location_final, review_final, rev_index, loc_index);
		int numlocation = 0;
		while((location_final[numlocation]) !=NULL){
			numlocation ++;
			}
		bus_final ->name = name;
		bus_final ->locations = location_final;
		bus_final ->num_locations = numlocation;
	}
	else if(strcasecmp(name, bst->bus_yelp->name) <0){
		bst->bus_yelp = bst->bus_yelp->left;
		}
	else if(strcasecmp(name, bst->bus_yelp->name) >0){
		bst->bus_yelp = bst->bus_yelp->right;
		}
	return bus_final;
}

	
void search_location(struct loc_self* location1, char* state, char* zip_code, struct Location* location2, struct Review* review, int* rev_index, int* loc_index)
{
	if(location1 ==NULL){
	  return;
		}
	FILE * getloctaion = fopen(business_path, "r");
	fseek(getloctaion, location1->offset, SEEK_SET );
	char * location_get = malloc(sizeof(char)* 6000);
	fgets(location_get, 6000, getloctaion);
	char ** location_separate= explode(location_get, "\t\n");
	if(state != NULL && zip_code!= NULL){
		if(strcasecmp(location_separate[4],state)==0){
			if(strcmp(location_separate[5],zip_code)==0){
			  location2[0]. address = location_separate[2];
			  location2[0]. city = location_separate[3];
			  location2[0]. state = location_separate[4];
			  location2[0]. zip_code = location_separate[5];
			  search_review(location1->rev_loc, review, rev_index);
			  int numreviews = 0;
			  while(review[numreviews] !=NULL){
			    numreviews ++;
			  }
			  location2[*loc_index]. reviews = review;
			  location2[*loc_index]. num_reviews = numreviews;
			  *loc_index = *loc_index+1;
			}
			else if(strcasecmp(location_separate[5],zip_code)<0){
			  search_location(location1->left, state,zip_code, location2, review, rev_index, loc_index);
			}
			else{	
			  search_location(location1->left, state,zip_code, location2, review, rev_index, loc_index);
			}
		}
		else if(strcasecmp(location_separate[4],state)<0){
		    search_location(location1->left, state,zip_code, location2, review, rev_index, loc_index);
		  }
		else{	
		  search_location(location1->left, state,zip_code, location2, review, rev_index, loc_index);
		}   
	}		  
	else if(state ==NULL && zip_code !=NULL){
	  if(location1 != NULL){
	    location1 = location1->left;
	    search_location(location1, state, zip_code, location2, review, rev_index, loc_index);
	    if(strcmp(location_separate[5],zip_code)==0){
	      location2[*loc_index]. address = location_separate[2];
	      location2[*loc_index]. city = location_separate[3];
	      location2[*loc_index]. state = location_separate[4];
	      location2[*loc_index]. zip_code = location_separate[5];
	      search_review(location1->rev_loc, review, rev_index);
	      int numreviews = 0;
	      while(review[numreviews] !=NULL){
		numreviews ++;
	      }
	      location2[*loc_index]. reviews = review;
	      location2[*loc_index]. num_reviews = numreviews;
	      loc_index++;
	    }
	    location1 = location1->right;
	    search_location(location1, state, zip_code, location2, review, rev_index, loc_index);
	  }
	}
	else if(state !=NULL && zip_code == NULL){
	  if(location1 != NULL){
	    location1 = location1 ->left;
	    search_location(location1, state, zip_code, location2, review, rev_index, loc_index);
	      if(strcmp(location_separate[4],zip_code)==0){
		location2[*loc_index]. address = location_separate[2];
		location2[*loc_index]. city = location_separate[3];
		location2[*loc_index]. state = location_separate[4];
		location2[*loc_index]. zip_code = location_separate[5];
		search_review(location->review, review, rev_index);
		int numreviews = 0;
		while(review[numreviews] !=NULL){
		  numreviews ++;
		}
		location2[*loc_index]. reviews = review;
		location2[*loc_index]. num_reviews = numreviews;
		loc_index++;
	      }
	    location1 = location1->right;
	    search_location(location1, state, zip_code, location2, review, rev_index, loc_index);
	  }
	}
	else{
	  if(location != NULL){
	    location1 = location1->left;
	    search_location(location1, state, zip_code, location2, review, rev_index, loc_index);
	    location2[*loc_index]. address = location_separate[2];
	    location2[*loc_index]. city = location_separate[3];
	    location2[*loc_index]. state = location_separate[4];
	    location2[*loc_index]. zip_code = location_separate[5];
	    search_review(location->review, review, rev_index);
	    int numreviews = 0;
	    while(review[numreviews] !=NULL){
	      numreviews ++;
	    }
	    location2[*loc_index]. reviews = review;
	    location2[*loc_index]. num_reviews = numreviews;
	    *loc_index = *loc_index+1;
	    location1 = location1->right;
	    search_location(location1, state, zip_code, location2, review, rev_index, loc_index);
	  }
	}
	return;
}

void search_review(struct rev_self* review, struct Review* review_array, int *rev_index)
{
	if(review ==NULL){
	  return;
	}
	FILE * getreivew = fopen(reviews_path, "r");
	fseek(getreivew, review->offset, SEEK_SET );
	char * review_get = malloc(sizeof(char)* 6000);
	fgets(review_get, 6000, getreview);
	char ** review_separate= explode(review_get, "\t\n");
	if( review!= NULL){
		review = review->left;
		search_review(review, review_array, &rev_index);
		review_array[*rev_index]. text = review_separate[5];
		review_array[*rev_index]. stars = review_separate[1];
		*rev_index = rev_index+1;
		review = review->right;
		search_review(review, review_array, rev_index);
	}	
	return;
}


char * * explode(const char * str, const char * delims)
{
  int N=0;
  int ind;
  int num;
  int arrInd = 0;
  int last = 0;
  for(ind = 0; str[ind] != '\0'; ind++)
    {
      if (strchr(delims, str[ind]) != NULL)
	{
	  N++;
	}
    }
  char * * strArr = malloc((N+1) * sizeof(char *));
  for(num = 0; str[num] != '\0'; num++)
    {
      if (strchr(delims, str[num]) != NULL)
	{
	  strArr[arrInd] = malloc((num-last+1)* sizeof(char));
	  memcpy(strArr[arrInd], str+last, num-last);
	  *(strArr[arrInd] + num - last) = '\0';
	  last = num +1;
	  arrInd++;
	}
    }
  strArr[arrInd] = malloc((num - last + 1) * sizeof(char));
  memcpy(strArr[arrInd], str+last, num-last);
  *(strArr[arrInd] + num - last) = '\0';

  return strArr;
}
