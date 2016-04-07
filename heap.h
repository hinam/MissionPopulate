/*
** Min Heap Module
** heap is based on keys
** But every heap element has a key and a dataIndex
*/
typedef unsigned int uint;
typedef struct item {
            float key;         // the key for deciding position in heap
            uint  dataIndex; // the payload index provided by the calling program
} HeapItem;

typedef struct heap {
		HeapItem *H; 		// the underlying array
		uint *map;		// map[i] is index into H of location of payload with dataIndex == i
		uint n;			// the number of items currently in the heap
		uint size; 		// the maximum number of items allowed in the heap
		uint size_map; //size of map,i.e.maximum vertexId in the map
} Heap;

#define HEAP_SUCCESS 1
#define HEAP_FAIL    0

//returns a pointer to a new, empty heap
Heap *createHeap();

//inserts dataIndex into h. Returns HEAP SUCCESS if it has inserted, or HEAP FAIL otherwise.
int insert(Heap *h, uint dataIndex, float key);

//returns the data index of the root.
uint peek(Heap *h);

// returns the key of the root.
float peekKey(Heap *h);

//removes the root, returns the data index to it, and re-heapifies (possibly changing other items map values).
uint removeMin(Heap *h);

 //adds delta to the key of dataIndex and then re-heapifies.
void changeKey(Heap *h, uint dataIndex, float delta);

//free any memory you might of alloced in heap creation.
void destroyHeap(Heap *h);

//Makes sure the parent is less than its children
void siftUp(Heap *h, int n,float key);

//makes sure children are less than their parent 
void siftDown(Heap *h, int N, float key);

//swaps two heapitems in a heap
void swap(Heap *h, uint pos_child, uint pos_parent);

//prints the heap
void print_heap(Heap *h);

