#include <stdio.h>

#define MAX 50

struct Edge
{
    int u, v, w;
};

struct Edge edge[MAX];
int parent[MAX]; // parent[i] is the leader of the set containing i

// Find the leader (root) of the set containing x
int find(int x)
{
    while (parent[x] != x)
        x = parent[x];

    return x;
}

// Join the sets of a and b
void unionSet(int a, int b)
{
    parent[find(a)] = find(b);
}

int main()
{
    int n, e, i, j;
    int count = 0, total = 0;
    char a, b;
    struct Edge temp;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v weight):\n");

    for (i = 0; i < e; i++)
    {
        scanf(" %c %c %d", &a, &b, &edge[i].w);

        edge[i].u = a - 'A'; // convert letter to index (A = 0)
        edge[i].v = b - 'A';
    }

    for (i = 0; i < n; i++)
        parent[i] = i; // every vertex is in its own set at first

    // Sort edges in increasing order of weight (bubble sort)
    for (i = 0; i < e - 1; i++)
    {
        for (j = 0; j < e - i - 1; j++)
        {
            if (edge[j].w > edge[j + 1].w)
            {
                temp = edge[j];
                edge[j] = edge[j + 1];
                edge[j + 1] = temp;
            }
        }
    }

    printf("\nEdges in the Minimum Spanning Tree:\n");

    for (i = 0; i < e && count < n - 1; i++)
    {
        // different leaders means no cycle, so the edge can be added
        if (find(edge[i].u) != find(edge[i].v))
        {
            unionSet(edge[i].u, edge[i].v);

            printf("%c - %c : %d\n",
                   'A' + edge[i].u,
                   'A' + edge[i].v,
                   edge[i].w);

            total += edge[i].w;
            count++;
        }
    }

    printf("\nTotal weight of MST = %d\n", total);

    return 0;
}
