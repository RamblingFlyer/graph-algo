#include <stdio.h>
#include <stdlib.h>

#define MAXV 100

typedef struct {
    int u, v, weight;
} Edge;

void kruskal(Edge *edges, int edgeCount, int V) {
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
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    Edge *edges = malloc(E * sizeof(Edge));

    printf("Enter edges in the format: a b weight\n");
    for (int i = 0; i < E; i++) {
        char u, v;
        int weight;
        scanf(" %c %c %d", &u, &v, &weight);
        edges[i].u = u - 'a'; // Convert character to integer index
        edges[i].v = v - 'a'; // Convert character to integer index
        edges[i].weight = weight;
    }

    kruskal(edges, E, V);

    free(edges);
    return 0;
}