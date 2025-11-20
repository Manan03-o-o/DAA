#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX


typedef struct {
    int vertex;
    int dist;
} HeapNode;

typedef struct {
    int size;
    int capacity;
    int *pos;
    HeapNode **array;
} MinHeap;

HeapNode* newNode(int v, int dist) {
    HeapNode* node = (HeapNode*)malloc(sizeof(HeapNode));
    node->vertex = v;
    node->dist = dist;
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    return heap;
}

void swapHeapNode(HeapNode** a, HeapNode** b) {
    HeapNode* t = *a;
    *a = *b;
    *b = t;
}

void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size &&
        heap->array[left]->dist < heap->array[smallest]->dist)
        smallest = left;

    if (right < heap->size &&
        heap->array[right]->dist < heap->array[smallest]->dist)
        smallest = right;

    if (smallest != i) {
        HeapNode *smallestNode = heap->array[smallest];
        HeapNode *iNode = heap->array[i];

        heap->pos[smallestNode->vertex] = i;
        heap->pos[iNode->vertex] = smallest;

        swapHeapNode(&heap->array[smallest], &heap->array[i]);
        heapify(heap, smallest);
    }
}

HeapNode* extractMin(MinHeap* heap) {
    if (heap->size == 0) return NULL;

    HeapNode* root = heap->array[0];
    HeapNode* lastNode = heap->array[heap->size - 1];

    heap->array[0] = lastNode;

    heap->pos[root->vertex] = heap->size - 1;
    heap->pos[lastNode->vertex] = 0;

    --heap->size;
    heapify(heap, 0);

    return root;
}

void decreaseKey(MinHeap* heap, int v, int dist) {
    int i = heap->pos[v];
    heap->array[i]->dist = dist;

    while (i && heap->array[i]->dist < heap->array[(i - 1) / 2]->dist) {
        heap->pos[heap->array[i]->vertex] = (i - 1) / 2;
        heap->pos[heap->array[(i - 1) / 2]->vertex] = i;
        swapHeapNode(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap *heap, int v) {
    return heap->pos[v] < heap->size;
}

// ----------- Graph ---------------------

typedef struct AdjListNode {
    int dest, weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct {
    AdjListNode **array;
    int V;
} Graph;

AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* node = (AdjListNode*)malloc(sizeof(AdjListNode));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjListNode*)malloc(V * sizeof(AdjListNode));
    
    for (int i = 0; i < V; i++)
        graph->array[i] = NULL;

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* node = newAdjListNode(dest, weight);
    node->next = graph->array[src];
    graph->array[src] = node;
}

// --------- Dijkstra --------------------

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V];

    MinHeap* heap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INF;
        heap->array[v] = newNode(v, dist[v]);
        heap->pos[v] = v;
    }

    heap->array[src] = newNode(src, 0);
    heap->pos[src] = src;
    dist[src] = 0;
    heap->size = V;

    decreaseKey(heap, src, dist[src]);

    while (heap->size != 0) {
        HeapNode* minNode = extractMin(heap);
        int u = minNode->vertex;

        AdjListNode* temp = graph->array[u];
        while (temp != NULL) {
            int v = temp->dest;

            if (isInMinHeap(heap, v) && dist[u] != INF &&
                temp->weight + dist[u] < dist[v]) {

                dist[v] = dist[u] + temp->weight;

                decreaseKey(heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("\nShortest distances from source %d:\n", src);
    for (int i = 0; i < V; i++)
        printf("To %d: %d\n", i, dist[i]);
}

// ----------- Main (User Input) -----------------

int main() {
    int V, E, src;
    
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    Graph* graph = createGraph(V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges in format: src dest weight\n");
    for (int i = 0; i < E; i++) {
        int s, d, w;
        scanf("%d %d %d", &s, &d, &w);
        addEdge(graph, s, d, w);
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src);

    return 0;
}