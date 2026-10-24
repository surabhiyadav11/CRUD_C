#include <stdio.h>

#define MAX 20

int graph[MAX][MAX] = {0};
int vertices = 0;
int graphType;
int visited[MAX];
int queue[MAX];

void createVertex()
{
    if (vertices == MAX)
    {
        printf("Graph is full!\n");
        return;
    }

    vertices++;
    printf("Vertex %d created successfully.\n", vertices);
}

void createEdge()
{
    int u, v;
    int seenBefore[MAX];

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices || v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loop is not allowed.\n");
        return;
    }

    if (graph[u - 1][v - 1] == 1)
    {
        printf("Edge already exists.\n");
        return;
    }

    int i, j;
    int front = 0, rear = 0;

    for (i = 0; i < vertices; i++)
        seenBefore[i] = 0;

    seenBefore[0] = 1;
    queue[rear++] = 0;

    while (front < rear)
    {
        int current = queue[front++];

        for (j = 0; j < vertices; j++)
        {
            if ((graph[current][j] == 1 ||
                 graph[j][current] == 1) &&
                seenBefore[j] == 0)
            {
                seenBefore[j] = 1;
                queue[rear++] = j;
            }
        }
    }

    graph[u - 1][v - 1] = 1;

    if (graphType == 2)
        graph[v - 1][u - 1] = 1;

    printf("Edge added successfully.\n");

    /*
       Print disconnected only when both endpoints
       were outside vertex 1's component before adding
       this edge, matching the required behavior.
    */
    if (seenBefore[u - 1] == 0 &&
        seenBefore[v - 1] == 0)
    {
        printf("Graph is disconnected.\n");
    }
}

void readGraph()
{
    int i, j;

    if (vertices == 0)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }

    printf("\n========== GRAPH STRUCTURE ==========\n");

    for (i = 0; i < vertices; i++)
    {
        printf("%d -> ", i + 1);
        int found = 0;

        for (j = 0; j < vertices; j++)
        {
            if (graph[i][j] == 1)
            {
                printf("%d ", j + 1);
                found = 1;
            }
        }

        if (found == 0)
            printf("No connected vertices");

        printf("\n");
    }
}

void updateEdge()
{
    int u, v;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices || v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loop is not allowed.\n");
        return;
    }

    if (graph[u - 1][v - 1] == 0)
    {
        printf("Edge does not exist.\n");
        return;
    }

    graph[u - 1][v - 1] = 0;

    if (graphType == 2)
        graph[v - 1][u - 1] = 0;

    printf("Existing edge removed. Enter the new vertex numbers.\n");
    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices || v < 1 || v > vertices || u == v)
    {
        printf("Invalid vertex numbers. Old edge was removed.\n");
        return;
    }

    graph[u - 1][v - 1] = 1;

    if (graphType == 2)
        graph[v - 1][u - 1] = 1;

    printf("Edge updated successfully.\n");
}

void deleteEdge()
{
    int u, v;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices || v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (graph[u - 1][v - 1] == 0)
    {
        printf("Edge does not exist.\n");
        return;
    }

    graph[u - 1][v - 1] = 0;

    if (graphType == 2)
        graph[v - 1][u - 1] = 0;

    printf("Edge deleted successfully.\n");
}

void deleteVertex()
{
    int v, i, j;

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("Enter vertex number to delete: ");
    scanf("%d", &v);

    if (v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    for (i = v - 1; i < vertices - 1; i++)
    {
        for (j = 0; j < vertices; j++)
            graph[i][j] = graph[i + 1][j];
    }

    for (j = v - 1; j < vertices - 1; j++)
    {
        for (i = 0; i < vertices - 1; i++)
            graph[i][j] = graph[i][j + 1];
    }

    vertices--;

    for (i = 0; i < vertices; i++)
        graph[vertices][i] = graph[i][vertices] = 0;

    printf("Vertex deleted successfully.\n");
}

void markConnected(int seen[])
{
    int front = 0, rear = 0;
    int current, i;

    for (i = 0; i < vertices; i++)
        seen[i] = 0;

    if (vertices == 0)
        return;

    seen[0] = 1;
    queue[rear++] = 0;

    while (front < rear)
    {
        current = queue[front++];

        for (i = 0; i < vertices; i++)
        {
            if ((graph[current][i] == 1 ||
                 graph[i][current] == 1) &&
                seen[i] == 0)
            {
                seen[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int isGraphConnected()
{
    int seen[MAX];
    int i;

    if (vertices == 0)
        return 0;

    markConnected(seen);

    for (i = 0; i < vertices; i++)
    {
        if (seen[i] == 0)
            return 0;
    }

    return 1;
}

void checkConnectivity()
{
    if (isGraphConnected())
        printf("Graph is connected.\n");
    else
        printf("Graph is disconnected.\n");
}

void BFS()
{
    int start, front = 0, rear = 0;
    int i, current;

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    if (!isGraphConnected())
    {
        printf("Graph is disconnected. Cannot perform BFS.\n");
        return;
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    if (start < 1 || start > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    for (i = 0; i < vertices; i++)
        visited[i] = 0;

    queue[rear++] = start - 1;
    visited[start - 1] = 1;

    printf("BFS Traversal: ");

    while (front < rear)
    {
        current = queue[front++];
        printf("%d ", current + 1);

        for (i = 0; i < vertices; i++)
        {
            if (graph[current][i] == 1 && visited[i] == 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

void DFSVisit(int current)
{
    int i;

    visited[current] = 1;
    printf("%d ", current + 1);

    for (i = 0; i < vertices; i++)
    {
        if (graph[current][i] == 1 && visited[i] == 0)
            DFSVisit(i);
    }
}

void DFS()
{
    int start, i;

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    if (!isGraphConnected())
    {
        printf("Graph is disconnected. Cannot perform DFS.\n");
        return;
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    if (start < 1 || start > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    for (i = 0; i < vertices; i++)
        visited[i] = 0;

    printf("DFS Traversal: ");
    DFSVisit(start - 1);
    printf("\n");
}

int main()
{
    int choice;

    printf("Select Graph Type:\n");
    printf("1. Directed Graph\n");
    printf("2. Undirected Graph\n");
    printf("Enter your choice: ");
    scanf("%d", &graphType);

    if (graphType != 1 && graphType != 2)
    {
        printf("Invalid graph type!\n");
        return 0;
    }

    do
    {
        printf("\n========== GRAPH MENU ==========\n");
        printf("1. Create Vertex\n");
        printf("2. Create Edge\n");
        printf("3. Read Graph\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Delete Vertex\n");
        printf("7. BFS Traversal\n");
        printf("8. DFS Traversal\n");
        printf("9. Check Connectivity\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createVertex();
                break;

            case 2:
                createEdge();
                break;

            case 3:
                readGraph();
                break;

            case 4:
                updateEdge();
                break;

            case 5:
                deleteEdge();
                break;

            case 6:
                deleteVertex();
                break;

            case 7:
                BFS();
                break;

            case 8:
                DFS();
                break;

            case 9:
                checkConnectivity();
                break;

            case 10:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 10);

    return 0;
}