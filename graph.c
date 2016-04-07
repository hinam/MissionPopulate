/*
** Graph data type
** Uses an adjacency list representation (arrays for lists).
** Written for Assignment 2 of COMP20007
**
** Hinam Mehra
** Sun 17 May 2015
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "set.h"
#include "heap.h"
#include "graph.h"


/*
** Create graph with number_of_vertices vertices
*/
Graph *
graph_new(int number_of_vertices) {
    assert(number_of_vertices > 0);

    Graph *g = NULL;

//    malloc space for g
    g = (Graph *)malloc(sizeof(Graph));
    assert(g);
    g->data = NULL;
    g->number_of_vertices = number_of_vertices;
    g->vertices = (Vertex *)malloc(sizeof(Vertex) * number_of_vertices);
    assert(g->vertices);
    int i;
  //  malloc space for number_of_vertices vertices
    for(i = 0; i < number_of_vertices; i++){
    	g->vertices[i].max_num_edges = 1;
    	g->vertices[i].num_edges = 0;
    	g->vertices[i].data  = 0;
    	g->vertices[i].label = i;
    	g->vertices[i].edges = (Edge *)malloc(sizeof(Edge));
    }
    return(g);
}

/*
** Add edge to g. 
*/
void  
graph_add_edge(Graph *g, Label v, Label u, float data) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);
		
       // Make room in g->vertices[v].edges if no room.
        if(g->vertices[v].max_num_edges == g->vertices[v].num_edges){
        	g->vertices[v].max_num_edges *= 2;
        	g->vertices[v].edges = (Edge *)realloc(g->vertices[v].edges, sizeof(Edge) * g->vertices[v].max_num_edges);
        }
        
       // add u and data to g->vertices[v].edges array
        Edge new_edge;
        new_edge.u = u;
        new_edge.data = data;
        
        Edge *edges_array = g->vertices[v].edges;
        int index = g->vertices[v].num_edges;
        edges_array[index] = new_edge;
        
       // increment g->vertices[v].num_edges
        g->vertices[v].num_edges += 1;
        
}

/*
** Delete edge from g. Only deletes one copy if there are multiple.
** Attributes to the Workshop 3 Solution for this function
*/
void  
graph_del_edge(Graph *g, Label v, Label u) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    int i;

    for(i = 0 ; i < g->vertices[v].num_edges && g->vertices[v].edges[i].u != u ; i++);
        
    if (i == g->vertices[v].num_edges) // not there
        return;

    for( ; i < g->vertices[v].num_edges - 1 ; i++) // move remainder to the left to fill hole at i
        g->vertices[v].edges[i] = g->vertices[v].edges[i+1];

    g->vertices[v].num_edges -= 1;
}


/*
** Return pointer to start of edge array for vertex v
** Set n to the number of items in the edge array.
*/
Edge *
graph_get_edge_array(Graph *g, Label v, int *num_edges) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

    *num_edges = g->vertices[v].num_edges;

    return g->vertices[v].edges;
}


/*
** Return 1 if (v,u) is in g
*/
int
graph_has_edge(Graph *g, Label v, Label u) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);
    
    int i;
    for(i = 0; i < g->vertices[v].num_edges; i++){
    	if(g->vertices[v].edges[i].u == u){
    		return 1;
    	}
    }

    return 0;
}

/*
** Set vertex's data to data
*/
void  
graph_set_vertex_data(Graph *g, Label v, int data) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    
    g->vertices[v].data = data;
}



/*
** Simple explore for calling from dfs that doesn't actually do anything.
** Use as a template for writing your own explore() functions.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
void 
graph_default_explore(Graph *g, Label v) {
    if (g->vertices[v].data)
        return;

    g->vertices[v].data = 1; // mark as visited

    for(int i = 0 ; i < g->vertices[v].num_edges ; i++)
        graph_default_explore(g, g->vertices[v].edges[i].u);
}


/*
** Perform DFS beginning at v, calling pre() and post() as appropriate.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
int
graph_dfs(Graph *g, Label v, void (explore)(Graph *g, Label v)) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

        // first explore from v
    
    explore(g, v);
    //count components. If number of components > 1, graph is not connected
    for(int i = 0; i < g->number_of_vertices; i++){
    	if(!(g->vertices[i].data)){
    		return NOT_CONNECTED;
    	}
    }
    return CONNECTED;
}

/*
** Sets all vertices in the graph as unvisited
*/
void set_vertex_unvisited(Graph *g){
	int i;
	for(i = 0; i < g->number_of_vertices; i++){
		g->vertices[i].data = 0;
	}
}

/*
** Prints the Graph
*/
void
print_graph(Graph *g){
	int V = g->number_of_vertices;
	int i,j;
	for(i = 0; i < V; i++){
		printf("Vertex = %d Visited = %d\n", g->vertices[i].label,g->vertices[i].data);
		int E = g->vertices[i].num_edges;
		for(j = 0; j < E; j++){
			int edge = g->vertices[i].edges[j].u;
			float edge_weight =  g->vertices[i].edges[j].data;
			if(edge >= 0){
				printf("EdgeLabel = %d Weight = %.2f\n",edge,edge_weight);
			}
		}
	}
		
}

/*
** Returns the index from array vertices of the argument label of vertex
*/
int get_vertex_index(Graph *g,Label l){
	int index = -1;
	int i;
	for(i = 0; i < g->number_of_vertices; i++){
		if(g->vertices[i].label == l && (!(g->vertices[i].data))){
			index = i;
			break;
		}
	}
	if(index >= 0){
		g->vertices[index].data = 1;
	}
	return index;

}

/*
** Calculates shortest path from source to all vertices in the graph
** Uses priority queue i.e. Heap
** Returns a Set of House vertices that are within DISTANCE KM of the source school
*/
HashSet *dijkstra(Graph *g, int source_vertexId,int n_H){
	
	int o,index;
	float dist_v1,dist_o,edge_weight;
	HashSet *s = create_set(source_vertexId);
	//initialise heap with dist values
	Heap *h = createHeap();
	insert(h,source_vertexId,0);
	int i;
	// set all dist values to infinity
	for(i = 0; i < g->number_of_vertices; i++){
		if(g->vertices[i].label != source_vertexId){
			insert(h,g->vertices[i].label,INT_MAX);
		}
	}
	//while heap is not empty
	while(h->n != 0){
			o = removeMin(h);
			index = get_vertex_index(g,o);
		if(h->H[h->map[o]].key <= DISTANCE && o >= 0 && o < n_H ){
			add_vertex(s,o);
		}
		int i;
		for(i = 0; i < g->vertices[index].num_edges; i++){
			dist_v1 = h->H[h->map[g->vertices[index].edges[i].u]].key;
			dist_o = h->H[h->map[o]].key;
			edge_weight = g->vertices[o].edges[i].data;
			if(dist_v1 > (dist_o + edge_weight)){
				dist_v1 = dist_o + edge_weight;
				changeKey(h,h->H[h->map[g->vertices[index].edges[i].u]].dataIndex,dist_v1);
			}	
		}
	}
	//free heap
	destroyHeap(h);
	return s;

}

/*
** Free's all the space allocated for graphs
*/
void destroyGraph(Graph *g){
	if(g == NULL){
		return;
	}
	if(g->number_of_vertices > 0){
		for(int i = 0; i < g->number_of_vertices; i++){
			if(g->vertices[i].num_edges > 0){
				free(g->vertices[i].edges);
			}
		}
		free(g->vertices);
	}
	free(g);
}





