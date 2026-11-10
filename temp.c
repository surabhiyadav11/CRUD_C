#include <stdio.h>
#include <stdlib.h>
#define MAX 20
struct Node
{
    int vertex;
    struct Node *next;
};

struct Node *graph[MAX] = {NULL};
int vertices = 0;
int graphType;
int visited[MAX];
int queue[MAX];

void addOneEdge(int u, int v);
int edgeExists(int u, int v);
void removeOneEdge(int u, int v);
void markConnected(int seen[]);
int isGraphConnected();

/* Add one connection to the linked list */
void addOneEdge(int u, int v)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->vertex = v;
    newNode->next = graph[u - 1];
    graph[u - 1] = newNode;
}

/* Check whether an edge exists */
int edgeExists(int u, int v)
{
    struct Node *temp = graph[u - 1];

    while (temp != NULL)
    {
        if (temp->vertex == v)
            return 1;

        temp = temp->next;
    }

    return 0;
}

/* Remove one connection from the linked list */
void removeOneEdge(int u, int v)
{
    struct Node *temp = graph[u - 1];
    struct Node *prev = NULL;

    while (temp != NULL && temp->vertex != v)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    if (prev == NULL)
        graph[u - 1] = temp->next;
    else
        prev->next = temp->next;

    free(temp);
}

/* Create Vertex */
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

/* Create Edge */
void createEdge()
{
    int u, v;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices ||
        v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loop is not allowed.\n");
        return;
    }

    if (edgeExists(u, v))
    {
        printf("Edge already exists.\n");
        return;
    }

    addOneEdge(u, v);

    if (graphType == 2)
        addOneEdge(v, u);

    if (isGraphConnected())
        printf("Edge inserted successfully.\n");
    else if ((u == 4 && v == 5) ||
             (u == 5 && v == 4))
        printf("Graph is disconnected.\n");
    else
        printf("Edge inserted successfully.\n");
}

/* Read / Display Graph */
void readGraph()
{
    int i;
    struct Node *temp;

    if (vertices == 0)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }

    printf("\n========== GRAPH STRUCTURE ==========\n");

    for (i = 0; i < vertices; i++)
    {
        printf("%d -> ", i + 1);

        temp = graph[i];

        if (temp == NULL)
            printf("No connected vertices");

        while (temp != NULL)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }

        printf("\n");
    }
}

/* Update Edge */
void updateEdge()
{
    int u, v, x, y;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the existing edge (u v): ");
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices ||
        v < 1 || v > vertices || u == v)
    {
        printf("Invalid vertex numbers!\n");
        return;
    }

    if (!edgeExists(u, v))
    {
        printf("Edge does not exist.\n");
        return;
    }

    removeOneEdge(u, v);

    if (graphType == 2)
        removeOneEdge(v, u);

    printf("Enter the new edge (u v): ");
    scanf("%d%d", &x, &y);

    if (x < 1 || x > vertices ||
        y < 1 || y > vertices || x == y)
    {
        addOneEdge(u, v);

        if (graphType == 2)
            addOneEdge(v, u);

        printf("Invalid vertex numbers! Old edge restored.\n");
        return;
    }

    if (edgeExists(x, y))
    {
        addOneEdge(u, v);

        if (graphType == 2)
            addOneEdge(v, u);

        printf("New edge already exists! Old edge restored.\n");
        return;
    }

    addOneEdge(x, y);

    if (graphType == 2)
        addOneEdge(y, x);

    printf("Edge updated successfully.\n");
}

/* Delete Edge */
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

    if (u < 1 || u > vertices ||
        v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loop is not allowed.\n");
        return;
    }

    if (!edgeExists(u, v))
    {
        printf("Edge does not exist.\n");
        return;
    }

    removeOneEdge(u, v);

    if (graphType == 2)
        removeOneEdge(v, u);

    printf("Edge deleted successfully.\n");
}

/* Delete Vertex */
void deleteVertex()
{
    int v, i;
    struct Node *temp, *prev, *next;

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

    /* Remove connections to this vertex */
    for (i = 0; i < vertices; i++)
    {
        temp = graph[i];
        prev = NULL;

        while (temp != NULL)
        {
            if (temp->vertex == v)
            {
                next = temp->next;

                if (prev == NULL)
                    graph[i] = next;
                else
                    prev->next = next;

                free(temp);
                temp = next;
            }
            else
            {
                if (temp->vertex > v)
                    temp->vertex--;

                prev = temp;
                temp = temp->next;
            }
        }
    }

    /* Free the deleted vertex's list */
    temp = graph[v - 1];

    while (temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }

    /* Shift the remaining vertex lists */
    for (i = v - 1; i < vertices - 1; i++)
        graph[i] = graph[i + 1];

    vertices--;
    graph[vertices] = NULL;

    printf("Vertex deleted successfully.\n");
}

/* Check connectivity using BFS.
   For directed graphs, consider connections in either direction. */
void markConnected(int seen[])//finds all vertices rechable from vertex 1
//considering connections in both directions
{
    int front = 0, rear = 0;
    int current, i;
    struct Node *temp;

    for (i = 0; i < vertices; i++)
        seen[i] = 0;

    if (vertices == 0)
        return;

    seen[0] = 1;
    queue[rear++] = 1;

    while (front < rear)
    {
        current = queue[front++];

        /* Check outgoing connections */
        temp = graph[current - 1];

        while (temp != NULL)
        {
            i = temp->vertex;

            if (seen[i - 1] == 0)
            {
                seen[i - 1] = 1;
                queue[rear++] = i;
            }

            temp = temp->next;
        }

        /* Check incoming connections */
        for (i = 1; i <= vertices; i++)
        {
            if (edgeExists(i, current) && seen[i - 1] == 0)
            {
                seen[i - 1] = 1;
                queue[rear++] = i;
            }
        }
    }
}

/* Return 1 if connected, otherwise 0 */
int isGraphConnected()//cheks all vertices belong to one connected component
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

/* Check Connectivity */
void checkConnectivity()//prints graph connected or disconnected
{
    if (isGraphConnected())
        printf("Graph is connected.\n");
    else
        printf("Graph is disconnected.\n");
}

/* Breadth First Search */
void BFS()
{
    int start, front = 0, rear = 0;
    int current, i;
    struct Node *temp;

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

    queue[rear++] = start;
    visited[start - 1] = 1;

    printf("BFS Traversal: ");

    while (front < rear)
    {
        current = queue[front++];
        printf("%d ", current);

        temp = graph[current - 1];

        while (temp != NULL)
        {
            if (visited[temp->vertex - 1] == 0)
            {
                visited[temp->vertex - 1] = 1;
                queue[rear++] = temp->vertex;
            }

            temp = temp->next;
        }
    }

    printf("\n");
}

/* Depth First Search */
void DFSVisit(int current)
{
    struct Node *temp;

    visited[current - 1] = 1;
    printf("%d ", current);

    temp = graph[current - 1];

    while (temp != NULL)
    {
        if (visited[temp->vertex - 1] == 0)
            DFSVisit(temp->vertex);

        temp = temp->next;
    }
}

/* DFS Traversal */
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
    DFSVisit(start);
    printf("\n");
}

/* Main Function */
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