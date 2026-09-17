#include <stdio.h>
#include <stdlib.h>
#define MAX 20
struct Node
{
    int vertex;
    struct Node *next;
};

struct Node *adj[MAX];
int visited[MAX];
int n;
void addEdge(int u, int v)
{
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}
void DFS(int v)
{
    struct Node *temp;
    visited[v] = 1;
    printf("%d ", v);
    temp = adj[v];
    while (temp != NULL)
    {
        if (visited[temp->vertex] == 0)
            DFS(temp->vertex);

        temp = temp->next;
    }
}
void BFS(int start)
{
    int queue[MAX];
    int front = 0, rear = 0;
    int v;
    struct Node *temp;
    visited[start] = 1;
    queue[rear++] = start;
    while (front < rear)
    {
        v = queue[front++];
        printf("%d ", v);
        temp = adj[v];
        while (temp != NULL)
        {
            if (visited[temp->vertex] == 0)
            {
                visited[temp->vertex] = 1;
                queue[rear++] = temp->vertex;
            }

            temp = temp->next;
        }
    }
}

int main()
{
    int edges, u, v, start, i;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        adj[i] = NULL;
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter edges (u v):\n");
    for (i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    for (i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nDFS Traversal: ");
    DFS(start);

    for (i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nBFS Traversal: ");
    BFS(start);
    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            printf("\nRemaining component - BFS: ");
            BFS(i);
        }
    }

    printf("\n");

    return 0;
}
