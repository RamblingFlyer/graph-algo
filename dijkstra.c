#include <stdio.h>
#include <stdlib.h>

#define INF 99999

void printStepHeader(int V) {
    printf("\n%-8s", "Step");
    for (int i = 0; i < V; i++)
        printf("d[v%d] ", i);
    printf("\n");
    for (int i = 0; i < 8 + V * 8; i++) printf("-");
    printf("\n");
}

void printStepRow(int step, int *dist, int V) {
    printf("%-8d", step);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("INF     ");
        else
            printf("%-8d", dist[i]);
    }
    printf("\n");
}

void printVisited(int *visited, int V) {
    printf("Visited Set: { ");
    for (int i = 0; i < V; i++)
        if (visited[i])
            printf("v%d ", i);
    printf("}\n");
}

void dijkstra(int **graph, int V, int src) {
    int *dist = malloc(V * sizeof(int));
    int *visited = calloc(V, sizeof(int));
    int *parent = malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    printf("\nDijkstra Algorithm - Trace from source v%d:\n", src);
    printStepHeader(V);
    printStepRow(0, dist, V);

    for (int step = 1; step <= V; step++) {
        int u = -1, min = INF;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        printf("\nStep %d: Visiting v%d\n", step, u);

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INF) {
                int newDist = dist[u] + graph[u][v];
                printf("  Trying v%d -> v%d: %d + %d = %d", u, v, dist[u], graph[u][v], newDist);

                if (newDist < dist[v]) {
                    printf(" --> Update! (old d[v%d] = %s%d)\n", v, dist[v] == INF ? "INF" : "", dist[v]);
                    dist[v] = newDist;
                    parent[v] = u;
                } else {
                    printf(" (no update)\n");
                }
            }
        }

        printStepRow(step, dist, V);
        printVisited(visited, V);
        printf("\n");
    }

    printf("Final shortest distances from source v%d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("d[v%d] = INF\n", i);
        else
            printf("d[v%d] = %d\n", i, dist[i]);
    }

    free(dist);
    free(visited);
    free(parent);
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Allocate memory for adjacency matrix
    int **graph = malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = malloc(V * sizeof(int));
        for (int j = 0; j < V; j++)
            graph[i][j] = (i == j) ? 0 : INF; // 0 for self-loops, INF otherwise
    }

    printf("Enter edges as: from to weight (e.g., 0 1 4):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        // If the graph is undirected, uncomment the following line:
        // graph[v][u] = w;
    }

    int src;
    printf("Enter source vertex (0 to %d): ", V - 1);
    scanf("%d", &src);

    dijkstra(graph, V, src);

    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
