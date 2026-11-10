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
void createVertex()
{
    if (vertices == MAX)
    {
        printf("Graph is full!\n");
        return;
    }

    vertices++;
    printf("Vertex %d added successfully.\n", vertices);
}
void createEdge()
{
    int u, v;
    struct Node *newNode;
    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }
    printf("Enter two vertex numbers (1 to %d): ", vertices);
    scanf("%d%d", &u, &v);
    if (u < 1 || u > vertices || v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }
    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }
    struct Node *temp = graph[u - 1];
    while (temp != NULL)
    {
        if (temp->vertex == v)
        {
            printf("Edge already exists!\n");
            return;
        }
        temp = temp->next;
    }
    newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = graph[u - 1];///connects it to vertex 2's existing list
    graph[u - 1] = newNode;//makes this node starting noode of vertex 2
//cretes reverse connectionn
    newNode = malloc(sizeof(struct Node));
    newNode->vertex = u;//stores 4 in node
    newNode->next = graph[v - 1];
    graph[v - 1] = newNode;

    printf("Edge added successfully.\n");
}
void readGraph()
{
    int i, isolatedVertex = 0;
    struct Node *temp;
    if (vertices == 0)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }
    for (i = 0; i < vertices; i++)
    {
        if (graph[i] == NULL)
        {
            isolatedVertex = 1;
            break;
        }
    }
    if (isolatedVertex == 1)
    {
        printf("Some vertices have no connections.\n");
        return;
    }
    printf("\nGraph Representation (Adjacency List):\n\n");

    for (i = 0; i < vertices; i++)
    {
        printf("%d -> ", i + 1);
        temp = graph[i];

        while (temp != NULL)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
void updateEdge()
{
    int u, v, choice, found = 0;
    struct Node *temp, *prev, *newNode;
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
        printf("Self-loops are not allowed.\n");
        return;
    }

    temp = graph[u - 1];
    while (temp != NULL)
    {
        if (temp->vertex == v)
        {
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (found == 1)
    {
        printf("Edge already exists between %d and %d.\n", u, v);
        printf("1. Remove Edge\nChoice: ");
        scanf("%d", &choice);
        if (choice != 1)
        {
            printf("Invalid choice!\n");
            return;
        }
        prev = NULL;
        temp = graph[u - 1];

        while (temp->vertex != v)
        {
            prev = temp;
            temp = temp->next;
        }

        if (prev == NULL)
            graph[u - 1] = temp->next;
        else
            prev->next = temp->next;

        free(temp);

        prev = NULL;
        temp = graph[v - 1];

        while (temp->vertex != u)
        {
            prev = temp;
            temp = temp->next;
        }

        if (prev == NULL)
            graph[v - 1] = temp->next;
        else
            prev->next = temp->next;

        free(temp);

        printf("Edge removed successfully.\n");
    }
    else
    {
        printf("No edge exists between %d and %d.\n", u, v);
        printf("1. Add Edge\nChoice: ");
        scanf("%d", &choice);

        if (choice != 1)
        {
            printf("Invalid choice!\n");
            return;
        }

        newNode = malloc(sizeof(struct Node));
        newNode->vertex = v;
        newNode->next = graph[u - 1];
        graph[u - 1] = newNode;

        newNode = malloc(sizeof(struct Node));
        newNode->vertex = u;
        newNode->next = graph[v - 1];
        graph[v - 1] = newNode;

        printf("Edge added successfully.\n");
    }
}
void deleteEdge()
{
    int u, v;
    struct Node *temp, *prev;

    if (vertices < 2)
    {
        printf("At least two vertices are required.\n");
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
        printf("Self-loops are not allowed.\n");
        return;
    }

    prev = NULL;
    temp = graph[u - 1];

    while (temp != NULL && temp->vertex != v)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("No edge exists between %d and %d.\n", u, v);
        return;
    }

    if (prev == NULL)
        graph[u - 1] = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    prev = NULL;
    temp = graph[v - 1];

    while (temp != NULL && temp->vertex != u)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL)
    {
        if (prev == NULL)
            graph[v - 1] = temp->next;
        else
            prev->next = temp->next;

        free(temp);
    }
    printf("Edgedeleted successfully.\n");
}
void deleteVertex()
{
    int v, i;
    struct Node *temp, *prev, *next;
    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }
    printf("Enter vertex number to delete (1 to %d): ", vertices);
    scanf("%d", &v);

    if (v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    for (i = 0; i < vertices; i++)
    {
        prev = NULL;
        temp = graph[i];

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
    temp = graph[v - 1];
    while (temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
    for (i = v - 1; i < vertices - 1; i++)
        graph[i] = graph[i + 1];

    vertices--;
    graph[vertices] = NULL;
    printf("Vertex deleted successfully.\n");
}
int main()
{
    int choice;

    do
    {
        printf("\n--- GRAPH CRUD MENU ---\n");
        printf("1. Create Vertex\n");
        printf("2. Create Edge\n");
        printf("3. Read Graph\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Delete Vertex\n");
        printf("7. Exit\n");
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
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 7);
    return 0;
}



