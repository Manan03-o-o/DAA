#include <stdio.h>
#include <limits.h>

#define INF 999999

typedef struct {
    int src, dest, weight;
} Edge;

void bellmanFord(int V, int E, Edge edges[], int src, int dist[]) {
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Negative cycle check
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Graph contains a negative weight cycle!\n");
            return;
        }
    }
}

int main() {
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    Edge edges[E];

    printf("Enter edges (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    int dist[V][V];

    // Run Bellman-Ford from every vertex
    for (int src = 0; src < V; src++) {
        bellmanFord(V, E, edges, src, dist[src]);
    }

    printf("\nAll-Pairs Shortest Path Matrix (Bellman-Ford):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
