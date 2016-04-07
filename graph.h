/*
** Graph data type
** Uses an adjacency list representation (arrays for lists).
** Written for Assignment 2 of COMP20007
**
** Hinam Mehra
** Sun 17 May 2015
*/
typedef int Label;   // a vertex label (should be numeric to index edge lists)


typedef struct {
    float  data;   // any data you want to store about an edge
    Label u;        // end vertex of edge
} Edge;

typedef struct {
    int 	data;        // any data you want to store about a vertex
    Label  label;        // this vertex's label
    Edge  *edges;        // array of edges [0..num_edges-1]
    int   num_edges;     // number of edges
    int   max_num_edges; // current malloced size of edges array, num_edges <= max_num_edges
} Vertex;

typedef struct {
    void    *data;              // any data you want to store about a graph
    int    number_of_vertices; // |V|
    Vertex *vertices;          // array of vertices [0..number_of_vertices-1]
} Graph;

#define DISTANCE 1000
#define CONNECTED 1
#define NOT_CONNECTED 0
// prototypes

Graph *graph_new(int number_of_vertices);
void  graph_add_edge(Graph *g, Label v, Label u, float data);

void  graph_del_edge(Graph *g, Label v, Label u);   

int   graph_has_edge(Graph *g, Label v, Label u);
Edge *graph_get_edge_array(Graph *g, Label v, int *num_edges);
void  graph_set_vertex_data(Graph *g, Label v, int data);
void destroyGraph(Graph *g);

void graph_default_explore(Graph *g, Label v);
int graph_dfs(Graph *g, Label v, void (explore)(Graph *g, Label v));

void print_graph(Graph *g);
int graph_is_connected(Graph *g);
HashSet *dijkstra(Graph *g, int source_vertexId,int n_H);
void set_vertex_unvisited(Graph *g);
