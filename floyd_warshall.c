#include <stdio.h>

#define INF 999999 /* A value larger than any possible path length */

/* Print the current distance matrix */
void printMatrix(int n, int dist[n][n], int step)
{
    if (step == -1)
        printf("\n--- Initial Distance Matrix D0 ---\n");
    else
        printf("\n--- Distance Matrix D%d ---\n", step + 1);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int n, e;
    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Invalid number of vertices\n");
        return 1;
    }

    printf("Enter number of edges: ");
    if (scanf("%d", &e) != 1 || e < 0)
    {
        fprintf(stderr, "Invalid number of edges\n");
        return 1;
    }

    int dist[n][n];

    // Initialize distance matrix
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = (i == j) ? 0 : INF;

    printf("Enter edges as: from to weight (0-based index)\n");
    for (int i = 0; i < e; ++i)
    {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3 || u < 0 || u >= n || v < 0 || v >= n)
        {
            fprintf(stderr, "Invalid edge input\n");
            return 1;
        }
        dist[u][v] = w; // For directed graph
        // If graph is undirected, also do: dist[v][u] = w;
    }

    /* Show the initial matrix as D0 */
    printMatrix(n, dist, -1);

    /* Floyd–Warshall core */
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        /* Print as D1, D2, ..., Dn */
        printMatrix(n, dist, k);
    }

    return 0;
}
