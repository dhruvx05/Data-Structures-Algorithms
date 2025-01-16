#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define V 5   // Number of vertices
#define E 8   // Number of edges

typedef struct {
    int u, v, weight;
} Edge;

// Utility function for Dijkstra
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index;
    for (int i = 0; i < V; i++)
        if (!visited[i] && dist[i] <= min)
            min = dist[i], min_index = i;
    return min_index;
}

// Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool visited[V] = {false};

    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printf("Dijkstra - Distance from source %d:\n", src);
    for (int i = 0; i < V; i++) printf("Vertex %d: %d\n", i, dist[i]);
}

// Bellman-Ford Algorithm
void bellmanFord(Edge edges[E], int src) {
    int dist[V];
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int weight = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printf("Bellman-Ford - Distance from source %d:\n", src);
    for (int i = 0; i < V; i++) printf("Vertex %d: %d\n", i, dist[i]);
}

int main() {
    int graph[V][V] = {
        {0, 6, 0, 0, 7},
        {0, 0, 5, -4, 8},
        {0, -2, 0, 0, 0},
        {2, 0, 7, 0, 0},
        {0, 0, -3, 9, 0}
    };

    Edge edges[E] = {
        {0, 1, 6}, {0, 4, 7}, {1, 2, 5},
        {1, 3, -4}, {1, 4, 8}, {3, 0, 2},
        {3, 2, 7}, {4, 2, -3}
    };

    int src = 0;
    clock_t start, end;

    // Run Dijkstra
    start = clock();
    dijkstra(graph, src);
    end = clock();
    printf("Dijkstra Execution Time: %.6f seconds\n\n",
           ((double)(end - start)) / CLOCKS_PER_SEC);

    // Run Bellman-Ford
    start = clock();
    bellmanFord(edges, src);
    end = clock();
    printf("Bellman-Ford Execution Time: %.6f seconds\n",
           ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}
