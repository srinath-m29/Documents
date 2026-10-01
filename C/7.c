#include <stdio.h>
#include <limits.h>

#define MAX 20

int graph[MAX][MAX]; // adjacency matrix (0 means no edge)
int visited[MAX];    // 1 if the vertex is already in the MST
int n;

int main()
{
    int e, i, j, u, v, w;
    char a, b;
    int min, total = 0, edges = 0;
    int from, to;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v weight):\n");

    for (i = 0; i < e; i++)
    {
        scanf(" %c %c %d", &a, &b, &w);

        u = a - 'A'; // convert letter to index (A = 0)
        v = b - 'A';

        graph[u][v] = w; // undirected graph, so store both sides
        graph[v][u] = w;
    }

    visited[0] = 1; // start from vertex A

    printf("\nEdges in the Minimum Spanning Tree:\n");

    while (edges < n - 1) // MST has n - 1 edges
    {
        min = INT_MAX;
        from = -1;
        to = -1;

        // find the smallest edge from a visited vertex to an unvisited vertex
        for (i = 0; i < n; i++)
        {
            if (visited[i])
            {
                for (j = 0; j < n; j++)
                {
                    if (!visited[j] &&
                        graph[i][j] != 0 &&
                        graph[i][j] < min)
                    {
                        min = graph[i][j];
                        from = i;
                        to = j;
                    }
                }
            }
        }

        if (to == -1) // no edge found, graph is disconnected
        {
            printf("Graph is not connected.\n");
            return 0;
        }

        visited[to] = 1; // add the new vertex to the MST

        printf("%c - %c : %d\n",
               'A' + from,
               'A' + to,
               min);

        total += min;
        edges++;
    }

    printf("\nTotal weight of MST = %d\n", total);

    return 0;
}
