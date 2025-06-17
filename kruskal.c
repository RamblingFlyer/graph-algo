#include <stdio.h>
#include <stdlib.h>

#define INF 99999
#define MAXV 100

typedef struct {
    int u, v, weight;
} Edge;

void kruskal(int **graph, int V) {
    Edge edges[MAXV * MAXV];
    int edgeCount = 0;

    // Step 1: Extract undirected edges (upper triangle only)
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != INF)
                edges[edgeCount++] = (Edge){i, j, graph[i][j]};
        }
    }

    // Step 2: Sort edges by weight
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Step 3: Partition using name array
    int name[MAXV];
    for (int i = 0; i < V; i++)
        name[i] = i;

    int totalWeight = 0;
    int edgeUsed = 0;

    printf("\nEdges selected for MST:\n");

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int setU = name[u];
        int setV = name[v];

        if (setU != setV && edgeUsed < V - 1) {
            // Accept edge
            printf("%d. %c - %c : %d\n", edgeUsed + 1, 'a' + u, 'a' + v, edges[i].weight);
            totalWeight += edges[i].weight;
            edgeUsed++;

            // Union
            int oldSet = name[v];
            for (int j = 0; j < V; j++)
                if (name[j] == oldSet)
                    name[j] = setU;
        } else {
            // Reject edge
            if (setU == setV)
                printf("Rejected edge at step %d (forms cycle): %c - %c : %d\n",
                       i + 1, 'a' + u, 'a' + v, edges[i].weight);
            else
                printf("Rejected edge at step %d (not needed): %c - %c : %d\n",
                       i + 1, 'a' + u, 'a' + v, edges[i].weight);
        }
    }

    printf("\nTotal Weight of MST: %d\n", totalWeight);
}

int main() {
    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    // Allocate adjacency matrix
    int **graph = malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        graph[i] = malloc(V * sizeof(int));

    printf("Enter the adjacency matrix (use %d for INF):\n", INF);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    kruskal(graph, V);

    // Free memory
    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
