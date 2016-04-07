/*
** Main module for Assignment 2, COMP20007(May 14,2015)
** Implemented by Hinam Mehra on May 14,2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "heap.h"
#include "graph.h"

    
int 
main(int argc, char *argv[]) {

	
	int n_H, n_S,n,max_size,total_v;
	int *v_1,*v_2;
	float *w;
	int vertex_1, vertex_2;
	float edge_weight;
	
	//Read the file from stdin
	scanf("%d",&n_H);
	scanf("%d",&n_S);
	total_v = n_H + n_S;
	max_size = n_S;
	n = 0;
	v_1 = malloc(sizeof(*v_1) * max_size);
	assert(v_1);
	v_2 = malloc(sizeof(*v_2) * max_size);
	assert(v_2);
	w = malloc(max_size * sizeof(*w));
	assert(w);
	
	while (scanf("%d %d %f",&vertex_1,&vertex_2,&edge_weight) == 3) {
		if(n >= max_size){
			max_size *= 2;
			v_1 = realloc(v_1,sizeof(*v_1) * max_size);
			v_2 = realloc(v_2,sizeof(*v_2) * max_size);
			w = realloc(w,sizeof(*w) * max_size);
		}
		// Input validation
		if(vertex_1 < 0 || vertex_1 > total_v){
			fprintf(stderr,"vertex out of range %d\n",vertex_1);
		}
		if(vertex_2 < 0 || vertex_2 > total_v){
			fprintf(stderr,"vertex out of range %d\n",vertex_2);
		}
		v_1[n]=vertex_1;
		v_2[n]=vertex_2;
		w[n] = edge_weight;
		n++;
	}
	// Creates a graph, adds all edges to the graph
	// Assumes that the graph is undirected
	Graph *g = graph_new(total_v);
	int i;
	for(i = 0; i < n; i++){
		graph_add_edge(g,v_1[i],v_2[i],w[i]);
		graph_add_edge(g,v_2[i],v_1[i],w[i]);
	}
	
	//Checks if the graph is connected
	if(!(graph_dfs(g,v_1[0],graph_default_explore))){
		fprintf(stderr,"Graph not connected\n");
	}
	//graph_dfs marks all elements visited if the graph is connected
	//This marks them unvisted for further calculations
	set_vertex_unvisited(g);
	
	int c,j;
	//For all the school vertices, run dijkstra's algorithm
	// And return a set which contains vertexId's of houses that are within 1Km of the school
	Sets_array *sa = create_sets_array(n_S);
	HashSet *s;
	for(c = 0; c < n_S; c++){
		s = dijkstra(g,n_H + c,n_H);
		add_set(sa,s);
		set_vertex_unvisited(g);
	}
	destroyGraph(g);
	//Creates a universal set which contains the vertexId's of all the houses
	HashSet *all = create_set(-1);
	for(j = 0; j < n_H; j++){
		add_vertex(all,j);
	}
	
	//Calculate set cover
	set_cover(all,sa,n_H);
	destroy(sa);
	return 0;
}