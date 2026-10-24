#include <stdio.h>
#include <stdlib.h>
struct Vertex;
struct AdjNode
{
    struct Vertex *vertex;
    struct AdjNode *next;
};
struct Vertex
{
    int id;
    int visited;
    struct AdjNode *adj;
    struct Vertex *next;
};
struct QueueNode
{
    struct Vertex *vertex;
    struct QueueNode *next;
};
struct Vertex *head = NULL;
struct Vertex *tail = NULL;
int vertices = 0;
int graphType;
/* Find a vertex using its number */
struct Vertex *findVertex(int id)
{
    struct Vertex *temp = head;

    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;

        temp = temp->next;
    }

    return NULL;
}
/* Check whether an edge exists */
int hasEdge(struct Vertex *u, struct Vertex *v)
{
    struct AdjNode *temp = u->adj;

    while (temp != NULL)
    {
        if (temp->vertex == v)
            return 1;

        temp = temp->next;
    }

    return 0;
}
/* Add one directed connection */
void addOneEdge(struct Vertex *u, struct Vertex *v)
{
    struct AdjNode *newNode = malloc(sizeof(struct AdjNode));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->vertex = v;
    newNode->next = u->adj;
    u->adj = newNode;
}
/* Remove one directed connection */
void removeOneEdge(struct Vertex *u, struct Vertex *v)
{
    struct AdjNode *temp = u->adj;
    struct AdjNode *prev = NULL;

    while (temp != NULL)
    {
        if (temp->vertex == v)
        {
            if (prev == NULL)
                u->adj = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
}
/* Add a vertex */
void createVertex()
{
    struct Vertex *newVertex;

    if (vertices == 20)
    {
        printf("Graph is full!\n");
        return;
    }
    newVertex = malloc(sizeof(struct Vertex));

    if (newVertex == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newVertex->id = ++vertices;
    newVertex->visited = 0;
    newVertex->adj = NULL;
    newVertex->next = NULL;

    if (head == NULL)
        head = newVertex;
    else
        tail->next = newVertex;

    tail = newVertex;

    printf("Vertex %d created successfully.\n", vertices);
}

/* Mark vertices reachable from vertex 1.
   Connections are checked in either direction,
   matching the original connectivity logic. */
void markConnected()
{
    struct Vertex *temp;
    struct Vertex *current;
    struct AdjNode *edge;
    struct QueueNode *front = NULL;
    struct QueueNode *rear = NULL;
    struct QueueNode *newNode;

    temp = head;

    while (temp != NULL)
    {
        temp->visited = 0;
        temp = temp->next;
    }

    if (head == NULL)
        return;

    head->visited = 1;

    newNode = malloc(sizeof(struct QueueNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->vertex = head;
    newNode->next = NULL;
    front = rear = newNode;

    while (front != NULL)
    {
        struct QueueNode *oldNode = front;
        current = front->vertex;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        free(oldNode);

        /* Follow outgoing connections */
        edge = current->adj;

        while (edge != NULL)
        {
            if (edge->vertex->visited == 0)
            {
                edge->vertex->visited = 1;

                newNode = malloc(sizeof(struct QueueNode));
                if (newNode == NULL)
                {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }

                newNode->vertex = edge->vertex;
                newNode->next = NULL;

                if (rear == NULL)
                    front = rear = newNode;
                else
                {
                    rear->next = newNode;
                    rear = newNode;
                }
            }

            edge = edge->next;
        }

        /* Also follow incoming connections */
        temp = head;

        while (temp != NULL)
        {
            if (hasEdge(temp, current) && temp->visited == 0)
            {
                temp->visited = 1;

                newNode = malloc(sizeof(struct QueueNode));
                if (newNode == NULL)
                {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }

                newNode->vertex = temp;
                newNode->next = NULL;

                if (rear == NULL)
                    front = rear = newNode;
                else
                {
                    rear->next = newNode;
                    rear = newNode;
                }
            }

            temp = temp->next;
        }
    }
}

/* Check whether all vertices are connected */
int isGraphConnected()
{
    struct Vertex *temp;

    if (head == NULL)
        return 0;

    markConnected();

    temp = head;

    while (temp != NULL)
    {
        if (temp->visited == 0)
            return 0;

        temp = temp->next;
    }

    return 1;
}

/* Create an edge */
void createEdge()
{
    int u, v;
    struct Vertex *source;
    struct Vertex *destination;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    source = findVertex(u);
    destination = findVertex(v);

    if (source == NULL || destination == NULL)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loop is not allowed.\n");
        return;
    }

    if (hasEdge(source, destination))
    {
        printf("Edge already exists.\n");
        return;
    }

    /* Remember which vertices were connected before */
    markConnected();

    int uWasVisited = source->visited;
    int vWasVisited = destination->visited;

    addOneEdge(source, destination);

    if (graphType == 2)
        addOneEdge(destination, source);

    printf("Edge added successfully.\n");

    if (uWasVisited == 0 && vWasVisited == 0)
        printf("Graph is disconnected.\n");
}

/* Display the adjacency list */
void readGraph()
{
    struct Vertex *temp;
    struct AdjNode *edge;

    if (head == NULL)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }

    printf("\n========== GRAPH STRUCTURE ==========\n");

    temp = head;

    while (temp != NULL)
    {
        printf("%d -> ", temp->id);

        edge = temp->adj;

        if (edge == NULL)
            printf("No connected vertices");

        while (edge != NULL)
        {
            printf("%d ", edge->vertex->id);
            edge = edge->next;
        }

        printf("\n");
        temp = temp->next;
    }
}

/* Update an existing edge */
void updateEdge()
{
    int u, v;
    struct Vertex *source;
    struct Vertex *destination;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    source = findVertex(u);
    destination = findVertex(v);

    if (source == NULL || destination == NULL)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loop is not allowed.\n");
        return;
    }

    if (!hasEdge(source, destination))
    {
        printf("Edge does not exist.\n");
        return;
    }

    removeOneEdge(source, destination);

    if (graphType == 2)
        removeOneEdge(destination, source);

    printf("Existing edge removed. Enter the new vertex numbers.\n");
    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    source = findVertex(u);
    destination = findVertex(v);

    if (source == NULL || destination == NULL || u == v)
    {
        printf("Invalid vertex numbers. Old edge was removed.\n");
        return;
    }

    if (!hasEdge(source, destination))
        addOneEdge(source, destination);

    if (graphType == 2 && !hasEdge(destination, source))
        addOneEdge(destination, source);

    printf("Edge updated successfully.\n");
}

/* Delete an edge */
void deleteEdge()
{
    int u, v;
    struct Vertex *source;
    struct Vertex *destination;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    source = findVertex(u);
    destination = findVertex(v);

    if (source == NULL || destination == NULL)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (!hasEdge(source, destination))
    {
        printf("Edge does not exist.\n");
        return;
    }

    removeOneEdge(source, destination);

    if (graphType == 2)
        removeOneEdge(destination, source);

    printf("Edge deleted successfully.\n");
}

/* Delete a vertex and all its connections */
void deleteVertex()
{
    int v;
    struct Vertex *temp = head;
    struct Vertex *prev = NULL;
    struct Vertex *current;
    struct Vertex *nextVertex;
    struct AdjNode *edge;

    if (head == NULL)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("Enter vertex number to delete: ");
    scanf("%d", &v);

    while (temp != NULL && temp->id != v)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    /* Remove all edges pointing to this vertex */
    current = head;

    while (current != NULL)
    {
        removeOneEdge(current, temp);
        current = current->next;
    }

    /* Free this vertex's adjacency list */
    edge = temp->adj;

    while (edge != NULL)
    {
        struct AdjNode *oldEdge = edge;
        edge = edge->next;
        free(oldEdge);
    }

    /* Remove the vertex from the linked list */
    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    if (tail == temp)
        tail = prev;

    free(temp);
    vertices--;

    /* Renumber remaining vertices */
    current = head;
    int id = 1;

    while (current != NULL)
    {
        current->id = id++;
        current = current->next;
    }

    printf("Vertex deleted successfully.\n");
}

/* Report connectivity */
void checkConnectivity()
{
    if (isGraphConnected())
        printf("Graph is connected.\n");
    else
        printf("Graph is disconnected.\n");
}

/* Breadth First Search using a linked queue */
void BFS()
{
    int start;
    struct Vertex *startVertex;
    struct Vertex *current;
    struct AdjNode *edge;
    struct QueueNode *front = NULL;
    struct QueueNode *rear = NULL;
    struct QueueNode *newNode;

    if (head == NULL)
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

    startVertex = findVertex(start);

    if (startVertex == NULL)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    current = head;

    while (current != NULL)
    {
        current->visited = 0;
        current = current->next;
    }

    startVertex->visited = 1;

    newNode = malloc(sizeof(struct QueueNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->vertex = startVertex;
    newNode->next = NULL;
    front = rear = newNode;

    printf("BFS Traversal: ");

    while (front != NULL)
    {
        struct QueueNode *oldNode = front;
        current = front->vertex;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        free(oldNode);

        printf("%d ", current->id);

        edge = current->adj;

        while (edge != NULL)
        {
            if (edge->vertex->visited == 0)
            {
                edge->vertex->visited = 1;

                newNode = malloc(sizeof(struct QueueNode));
                if (newNode == NULL)
                {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }

                newNode->vertex = edge->vertex;
                newNode->next = NULL;

                if (rear == NULL)
                    front = rear = newNode;
                else
                {
                    rear->next = newNode;
                    rear = newNode;
                }
            }

            edge = edge->next;
        }
    }

    printf("\n");
}

/* Depth First Search using recursion */
void DFSVisit(struct Vertex *current)
{
    struct AdjNode *edge;

    current->visited = 1;
    printf("%d ", current->id);

    edge = current->adj;

    while (edge != NULL)
    {
        if (edge->vertex->visited == 0)
            DFSVisit(edge->vertex);

        edge = edge->next;
    }
}

/* Start DFS */
void DFS()
{
    int start;
    struct Vertex *temp;
    struct Vertex *startVertex;

    if (head == NULL)
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

    startVertex = findVertex(start);

    if (startVertex == NULL)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    temp = head;

    while (temp != NULL)
    {
        temp->visited = 0;
        temp = temp->next;
    }

    printf("DFS Traversal: ");
    DFSVisit(startVertex);
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
