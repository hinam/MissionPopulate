/*
** Header Module for HashSet
** Implemented by Hinam Mehra for Assignment 2, COMP20007(May 14,2015)
**
*/

typedef unsigned int intu;

typedef struct{
		intu vertexId;
		int hashid;
} HashItem;

typedef struct{
		intu source_vertexId;     //Id of the source vertex
		HashItem *hashmap;			//indexed at vertexId, stores HashItem
		intu *ids;  // array storing all vertices of the set
		int i;			// number of elements in set
		int size;		//maximum number of elements in set 
		int map_size; //maximum vertexId in hashmap
	
} HashSet;


typedef struct {             
    int    n; 				//size
    HashSet **set;          //array of sets
} Sets_array;


#define SUCCESS 1;
#define FAIL 0;
#define HASH 50

//Creates an empty sets_array
Sets_array *create_sets_array(int num_schools); 

//Creates an empty set
HashSet *create_set(intu source_vertexId); 

//Checks if a vertexId is in a set particularly in the hashmap of the set
int contains(HashSet *s,intu vertexId); 

//Adds a vertex to the set
int add_vertex(HashSet *s,intu vertexId);

//returns a set with elements in both s1 and s2
HashSet *intersect(HashSet *s1, HashSet *s2); 

//Returns a set with elements in s1 which are not in s2
HashSet *set_difference(HashSet *s1, HashSet *s2); 

//prints sets_array
void print_sets_array(Sets_array* sa);

//prints set
void print_set(HashSet *s);

//frees all space allocated
void destroy(Sets_array *sa);

//adds a set of sets_array
int add_set(Sets_array *sa, HashSet *s);

//removes a set from sets_array	
int remove_set(Sets_array *sa, HashSet *s);

//calculates the set cover 
void set_cover(HashSet *mainset, Sets_array *subset,int n_H);

//returns the index of a set which has maximum uncovered elements
HashSet *max_uncovered(HashSet *uncovered, Sets_array *subset);
