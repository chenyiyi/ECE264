#include "answer10.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// In order to add the "offset", rewriting each struct
struct Review_t {
	long offset;               /* The offset of Text of the review */
};

struct Location_t {
	char* address;              /* just the street address */
	char* city;                 /* city name */
	char* state;                /* 2 uppercase letters */
	char* zip_code;             /* 5 digits */
	struct Review_t* reviews;   /* ARRAY of Review struct objects */
	uint32_t num_reviews;       /* size of the above array */
};

struct Business_t {
	int id;
	char* name;						/* Business name, e.g., "McDonald's" */
	struct Location_t* locations;	/* ARRAY of Location struct objects */
	uint32_t num_locations;			/* size of the above array */
	/* Note that we do not include the average star rating with the Business. */
};

// The definition of BSTnode
typedef struct BSTnode {
	struct Business_t* business;
	struct BSTnode* right;
	struct BSTnode* left;
}BSTnode;

 // Define BST
 struct YelpDataBST {
	struct BSTnode* root;
	FILE* file;				// reviews_file
};

 /* for test */
// inorder of bst
void _inorder(struct BSTnode* root) {
	if( root ==NULL ) return ;
	_inorder( root->left );
	printf( "business = %s\n" , root->business->name );
	_inorder( root->right );
}
void inorder(struct YelpDataBST* bst) {
	_inorder( bst->root );
}
/* end -- for test*/

/*	copy and malloc to str
 */
char * copy_str(const char * s) {
	int n;
	char * t;  /* note that if using const char *t, then the strcpy(t, s) below will have a warning. */
	if (s==NULL) return NULL;

	n = strlen(s)+1;  
	t = (char *)malloc(n*sizeof(char)); 

	// malloc returns void *, change the type to char *. Size of a char is always a byte
	if (t != NULL)
	  strcpy(t,s);  // Including the terminating null byte of s, s is copied to t.
	else
	  printf("in copy_str(), malloc return NULL\n");
	return t;
}

// --[ create bst ]--------------------------------------------------------------
// insert a node to bst
void insert_BSTnode(struct YelpDataBST* bst, struct BSTnode* node) {
	BSTnode *f, *p, *root;
	int isLeft, t;	// Record whether the current node is left subtree of its parent node

	// root == NULL 
	if( bst->root==NULL ) {
		bst->root = node;
		return ;
	}

	root = bst->root;
	p = root;	// p pointer to current node
	f = root;	// f pointer to father node of current node
	while( p ) {
		t = strcmp(p->business->name, node->business->name);
		// On both sides to search
		if( t <0 ) {
			f = p;
			p = p->right;
			isLeft = 0;
		}
		else if( t >0 ) {
			f = p;
			p = p->left;
			isLeft = 1;
		}
		else {
			break;
		}
	}
	// while p==NULL, find new insertion position
	if( p==NULL ) {
		if( isLeft ) {
			f->left = node;

		}else {
			f->right = node;
		}
	}	
	else {	// else , insert location of finding position
		struct Business_t* bis = p->business;
		bis->locations = (struct Location_t*)realloc( bis->locations, (bis->num_locations+1)*sizeof(struct Location_t) );
		bis->locations[ bis->num_locations ] = node->business->locations[0];
		bis->num_locations ++;
	}

	bst->root = root;
	return ;
}

int max = 0;
struct Review_t* get_next_review( FILE* reviews_file, int* id ) {
  // int stars;
	long offset;
	struct Review_t* review;
	char str[10000];

	if( feof(reviews_file) ) return NULL;

	//memset(str, '\0', sizeof(char) );
	offset = ftell( reviews_file );
	fscanf( reviews_file, "%d", id );
	//fprintf(stderr, "id = %d\n", *id );
	fgets( str, 10000, reviews_file );
	//max = strlen(str) > max ? strlen(str) : max;
	
	review = (struct Review_t*)malloc( sizeof(struct Review_t) );
	review->offset = offset;

	return review;
}

/* This function reads the two files and creates an index that can be used
 * to search the data and quickly retrieve the reviews.
 */
struct YelpDataBST* create_business_bst(const char* businesses_path,
                                        const char* reviews_path) {
	FILE* businesses_file;
	FILE* reviews_file;
	struct YelpDataBST* bst;
	struct BSTnode* node;
	struct Review_t* review;
	char str[1000];
	int id;

	bst = (struct YelpDataBST*)malloc( sizeof(struct YelpDataBST) );
	bst->root = NULL;

	// open file
	businesses_file = fopen(businesses_path, "r");
	reviews_file = fopen(reviews_path, "r");
	if( businesses_file==NULL || reviews_file==NULL ) {
		printf( "open file error!\n" );
		exit(1);
	}
	bst->file = reviews_file;
	
	review = NULL;
	// read data from businesses_file
	while( fgets(str, 1000, businesses_file) ) {
		// new node
		node = (struct BSTnode*)malloc( sizeof(struct BSTnode) );
		node->left = NULL;
		node->right = NULL;
		node->business = (struct Business_t*)malloc( sizeof(struct Business_t) );

		struct Business_t* bis = node->business;
		bis->num_locations = 1;
		bis->locations = (struct Location_t*)malloc( sizeof(struct Location_t) );

		struct Location_t* loc = bis->locations;
		loc->num_reviews = 0;
		loc->reviews = NULL;

		// handle input
		char *delim = "\t";
		bis->id = atoi( strtok(str, delim) );
		bis->name = copy_str( strtok(NULL, delim) );
		loc->address = copy_str( strtok(NULL, delim) );
		loc->city = copy_str( strtok(NULL, delim) );
		loc->state = copy_str( strtok(NULL, delim) );
		loc->zip_code = copy_str( strtok(NULL, delim) );
		fprintf(stderr, "Load id : %d\n" , bis->id );
		
		// read data from reviews_file
		while( 1 ) {
			if( review == NULL ) {
				if( (review = get_next_review( reviews_file, &id ))==NULL )break;
			}
			if( bis->id == id ) {
				loc->reviews = (struct Review_t*)realloc( loc->reviews, (loc->num_reviews+1)*sizeof(struct Review_t) );
				if( loc->reviews ==NULL ) {
					printf( "realloc error!\n" );
					exit(1);
				}
				loc->reviews[ loc->num_reviews ] = *review;
				loc->num_reviews ++;
				if( (review = get_next_review( reviews_file, &id ))==NULL )break;
			}
			else {
				break;
			}	
		}
		
		insert_BSTnode(bst, node);
	}
	
	//fprintf(stderr, "max = %d\n" , max );
	fclose(businesses_file);
	return bst;
}

// --[ select data ]--------------------------------------------------------------
/* copy location_t to location 
 */
struct Location* copy_location( struct Location_t* loc, FILE* file ) {
	int i, stars;
	struct Location* copy;
	FILE* file_t = file;
	char str[10000];

	copy = (struct Location*)malloc( sizeof(struct Location) );
	copy->address = copy_str(loc->address);
	copy->city = copy_str(loc->city);
	copy->state = copy_str(loc->state);
	copy->zip_code = copy_str(loc->zip_code);
	copy->num_reviews = loc->num_reviews;
	copy->reviews = NULL;

	if( copy->num_reviews >0 ) {
		copy->reviews = (struct	Review*)malloc( sizeof(struct Review)*copy->num_reviews );
		for( i=0 ; i<copy->num_reviews ; i++ ) {
			// transform offset to actually review text
			fseek( file_t, loc->reviews[i].offset, SEEK_SET);
			fscanf( file_t, "%*d %d %*d %*d %*d ", &stars );
			copy->reviews[i].stars = stars;
			fgets(str, 10000, file_t);
			copy->reviews[i].text = copy_str(str);
		}
	}
	/*
	for( i=0 ; i<copy->num_reviews ; i++ ) {
		printf( "%d, %s\n" , i, copy->reviews[i].text );
	}
	*/

	return copy;
}

/* copy Business_t to Business ,and
 * state code and ZIP code to filter locations by, or NULL
 * to include all states.
 */
struct Business* copy_filte_business( struct Business_t* business, char* state, char* zip_code, FILE* file ) {
	int i;
	struct Business* ret;
	struct Location_t *loc_t;
	
	ret = (struct Business*)malloc( sizeof(struct Business) );
	ret->name = copy_str(business->name);
	ret->locations = NULL;
	ret->num_locations = 0;
	
	for( i=0 ; i<business->num_locations ; i++ ) {
		loc_t = &(business->locations[i]);
		if( (state==NULL || !strcmp(state, loc_t->state)) &&
			(zip_code==NULL || !strcmp(zip_code, loc_t->zip_code)) ) {	// Using state and ZIP_code to filter locations by
				ret->locations = (struct Location*)realloc( ret->locations, (ret->num_locations+1)*sizeof(struct Location) );
				ret->locations[ ret->num_locations ] = *copy_location( loc_t, file );
				ret->num_locations ++;
		}
	}
	/*
	struct Business* bis = ret;
	printf( "num_locations = %d\n" , bis->num_locations );
	for( int i=0 ; i<bis->num_locations ; i++ ) {
		printf( "location = %s\n", bis->locations[i].address );
	}printf( "\n" );
	*/

	return ret;
}

// comparsive funcation of sorted
int cmp_location( const void* a, const void* b ) {
	int cmp_state, cmp_city, cmp_address;
	struct Location* l1 = (struct Location*)b;
	struct Location* l2 = (struct Location*)a;

	cmp_state = strcmp(l1->state, l2->state);
	if( !cmp_state ) {

		cmp_city = strcmp(l1->city, l2->city);
		if( !cmp_city ) {

			cmp_address = strcmp(l1->address, l2->address);
			return cmp_address;
		}
		else return cmp_city;
	}
	else return cmp_state;
}
int cmp_review( const void* a, const void* b ) {
	struct Review* r1 = (struct Review*)b;
	struct Review* r2 = (struct Review*)a;

	int stars = r1->stars - r2->stars;
	if( !stars ) {
		int cmp_city = strcmp(r1->text, r2->text);
		return cmp_city;
	}
	else return stars;
}

/* get_business_reviews(...) should return a pointer to a Business struct object
 * on the heap.  That object will include links to the individual locations.
 */
struct Business* get_business_reviews(struct YelpDataBST* bst,
                                      char* name, char* state, char* zip_code) {
	int i, t;
	struct BSTnode *p;
	struct Business* ret;
	struct Location *loc;

	// find business
	p = bst->root;
	while( p ) {
		t = strcmp(p->business->name, name);
		// On both sides to search
		if( t <0 ) {
			p = p->right;
		}
		else if( t >0 ) {
			p = p->left;
		}
		else {	// if p->data == node->data , find it
			break;
		}
	}
	// can't find the business that be called
	if( p==NULL ) return NULL;

	// copy information of finding business to returning business
	ret = copy_filte_business( p->business, state, zip_code, bst->file );

	/*
	struct Business* bis = ret;
	printf( "num_locations = %d\n" , bis->num_locations );
	for( int i=0 ; i<bis->num_locations ; i++ ) {
		printf( "location = %s\n", bis->locations[i].address );
	}printf( "\n" );
	*/

	// Locations must be sorted by state >> city >> address.
	qsort( ret->locations, ret->num_locations, sizeof(struct Location), cmp_location );

	for( i=0 ; i<ret->num_locations ; i++ ) {
		// Reviews must be sorted by star rating (descending) >> text of review.
		loc = &(ret->locations[i]);
		qsort( loc->reviews, loc->num_reviews, sizeof(struct Review), cmp_review );
	}
	
	return ret;
}

// --[ deallocate memory ]--------------------------------------------------------------------
/* Deallocate all memory allocated for the object returned by
 * create_business_bst(..) and close the files. */
void destroy_business_bst_t(struct BSTnode* root) {
	if( root==NULL ) return ;

	destroy_business_bst_t( root->left );
	destroy_business_bst_t( root->right );

	struct Business_t* bis = root->business;
	if( bis!=NULL ) {
		struct Location_t* loc = bis->locations;
		if( loc->reviews !=NULL ) {
			free( loc->reviews );
		}
		free( loc );
		free( bis );
	}
	free( root );
}
void destroy_business_bst(struct YelpDataBST* bst) {
	fclose(bst->file);
	destroy_business_bst_t( bst->root );
}

/* Deallocate all heap memory tied to an object returned by
 * get_business_reviews(..). */
void destroy_business_result(struct Business* b) {
	if( b!=NULL ) {
		struct Location* loc = b->locations;
		if( loc->reviews !=NULL ) {
			free( loc->reviews->text );
			free( loc->reviews );
		}
		free( loc );
		free( b );
	}
}
