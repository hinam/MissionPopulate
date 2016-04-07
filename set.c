/*
** HashSet Module
** Stores a key value for every Vertex
** Implements constant Add and Lookup
** Implemented for Assignment 2 COMP20007 by Hinam Mehra(May14,2015)
*/


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "set.h"

/*
** Creates an array of set for the number of school vertices
** Returns a Sets_array pointer 
*/
Sets_array *create_sets_array(int num_schools){
	Sets_array *sa = (Sets_array *)malloc(sizeof(Sets_array) * num_schools);
	assert(sa);
	sa->set = (HashSet **)malloc(sizeof(HashSet) * num_schools);
	assert(sa->set);
	sa->n = 0;
	return sa;
}

/*
** Creates a NULL set of the source vertexId
** Allocates initial memory for set components
** Returns a pointer to the set
*/
HashSet *create_set(intu source_vertexId){

	HashSet *s = (HashSet *)malloc(sizeof(HashSet));
	assert(s);
	
	s->source_vertexId = source_vertexId;
	s->i = 0;
	s->size = 1;
	s->map_size = 1;
	//s->cost = 0;
	
	s->ids = (intu *)malloc(sizeof(intu) * s->size);
	assert(s->ids);
	
	s->hashmap = (HashItem *)malloc(sizeof(HashItem) * s->map_size);
	assert(s->hashmap);
	return s;
}

/*
** Adds a vertex to the Given Set
** Returns SUCCESS if successfully inserted
*/
int 
add_vertex(HashSet *s,intu vertexId){
	assert(s);
	// No space in ids array
	if(s->i == s->size){
		s->size *= 2;
		s->ids = (intu *)realloc(s->ids, sizeof(intu) * s->size);
		assert(s->ids);
	}
	// increase size of hashmap which is indexed by vertexId's
	if(vertexId > s->map_size){
		s->map_size = vertexId + 1;
		s->hashmap = (HashItem *)realloc(s->hashmap,sizeof(HashItem) * s->map_size);
		assert(s->hashmap);
		
	}
	//set cannot contain duplicate elements
	if(contains(s,vertexId)){
		return FAIL;
	}
	
	
	s->hashmap[vertexId].vertexId = vertexId;
	s->hashmap[vertexId].hashid = HASH;
	
	s->ids[s->i] = vertexId;
	s->i++;
	
	return SUCCESS;
}

/*
** Adds a Set to sets array
** Returns SUCCESS when set is inserted
*/
int add_set(Sets_array *sa, HashSet *s){
	assert(sa);
	assert(s);
	
	sa->set[sa->n] = s;
	sa->n++;
	return SUCCESS;
}

/*
** Checks if a vertexId is in a Set
** Return SUCCESS if it does exist
*/
int contains(HashSet *s,intu vertexId){
	if(s->hashmap[vertexId].vertexId == vertexId && s->hashmap[vertexId].hasid == HASH){
		return SUCCESS;
	}
	return FAIL;
}

/*
** Calculates the intersection of two sets
* Returns the intersection set
*/
HashSet *intersect(HashSet *s1, HashSet *s2){
	HashSet *intersect = create_set(-1);
	int c;
	for(c = 0; c < s1->i; c++){
		if(contains(s2,s1->ids[c])){
			add_vertex(intersect,s1->ids[c]);
		}
	}
	return intersect;
}


/*
** Calculates set difference i.e. s1 - s2
** Returns the set which has elements from s1 which are not in s2
*/
HashSet *set_difference(HashSet *s1, HashSet *s2){
	HashSet *difference = create_set(-1);
	int c;
	for(c = 0; c < s1-> i; c++){
		if(!(contains(s2,s1->ids[c]))){
			add_vertex(difference,s1->ids[c]);
		}
	}
	return difference;
}

/*
** Prints all the sets in a sets_array
*/
void print_sets_array(Sets_array* sa){
	assert(sa);
	int i;
	for(i = 0 ; i < sa->n ; i++){
		print_set(sa->set[i]);
	}
}

/*
** Prints the set
*/
void print_set(HashSet *s){
	assert(s);
	printf("\n-----------------------\n");
	printf("Source : %d\n", s->source_vertexId);
	printf("n : %d\n", s->i);
	printf("Vertex Id: \n");
	int c;
	for(c = 0; c < s->i; c++){
		printf("%d ",s->ids[c]);
	}
	printf("\n");
	printf("\n-----------------------\n");
}


/*
** removes a set from sets_array
** Returns SUCCESS if the removal is successfull
*/

int remove_set(Sets_array *sa, HashSet *s){
	assert(sa);
	assert(s);
	
	int index = 0,i;
	for(i = 0; i < sa->n; i++){
		if(sa->set[i]->source_vertexId == s->source_vertexId){
			index = i;
			break;
		}
	}
	
	for(i = index; i < sa->n-1; i++){
		sa->set[i] = sa->set[i+1];
	}
	sa->n--;
	return SUCCESS;
}

/*
** Frees all space allocated for sets_array and sets
*/
void destroy(Sets_array *sa){
	if(sa == NULL){
		return;
	}
	int i,j;
	if(sa->n > 0){
		for(i=0; i < sa->n; i++){
			if(sa->set[i]->size > 0){
				for(j = 0; j < sa->set[i]->size; j++){
					free(sa->set[i]->ids);
					free(sa->set[i]->hashmap);
				}
			}
			free(sa->set[i]);
		}
	}
	return;
}

/*
** Calculates the minimum number of sets required from sets_array subset
** that cover all the elements in HashSet
** Implements a greedy approach.
** Returns void, but prints out set indices
*/

void set_cover(HashSet *mainset, Sets_array *subset,int n_H){
	HashSet *uncovered = mainset;
	HashSet *chosen;
	
	
	while(uncovered->i > 0){
		// choose the set with maximum uncovered elements
		chosen = max_uncovered(uncovered,subset);
		if(chosen){	
			// prints the school vertex id from 0..S-1
			printf("%d\n",chosen->source_vertexId - n_H);
			remove_set(subset,chosen);
			// subtract all elements from uncovered that were covered by chosen
			uncovered = set_difference(uncovered,chosen);
		}
		//There is atleast one element in mainset that is not covered by all the elements
		// in different sets of sets_array
		else{
			printf("No set cover\n");
		}
	}
	
}


/*
** Returns the index of the set from sets_array which has maximum
** number of uncovered elements
*/


HashSet *max_uncovered(HashSet *uncovered, Sets_array *subset){
	int num_uncovered = 0;
	HashSet *chosen;
	HashSet *set_intersect;
	int x;
	for(x = 0; x < subset->n ; x++){
		// calculates uncovered elements in a set
		set_intersect = intersect(subset->set[x],uncovered);
		if(set_intersect->i > num_uncovered){
			num_uncovered = set_intersect->i;
			chosen = subset->set[x];
		}
	
	}
	if(num_uncovered > 0){
		return chosen;
	}
	return FAIL;

}
