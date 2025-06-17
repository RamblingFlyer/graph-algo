#include <stdio.h>

#define INF 999999   /* A value larger than any possible path length */

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
    int n;
    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Invalid n\n");
        return 1;
    }

    int dist[n][n];

    printf("Enter adjacency matrix (%d×%d):\n"
           "(Use %d for no edge)\n", n, n, INF);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &dist[i][j]);

    /* Show the initial matrix as D0 */
    printMatrix(n, dist, -1);

    /* Floyd–Warshall core */
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

        /* Print as D1, D2, ..., Dn */
        printMatrix(n, dist, k);
    }

    return 0;
}
