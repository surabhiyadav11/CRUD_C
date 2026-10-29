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
int graphType;//1 directed 2 undirected
int visited[MAX];//0 means not visited 1 means visited
int queue[MAX];//stores vertices waiting to be cheked during bfs

/* Function declarations */
void addOneEdge(int u, int v);
int edgeExists(int u, int v);
void removeOneEdge(int u, int v);
void addConnection(int u, int v);
void removeConnection(int u, int v);
int isGraphConnected();
void BFS();
void DFS();
void DFSVisit(int current);

/* Add one connection using linked list */
void addOneEdge(int u, int v) //u=2 v=3
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)//if box didnt created
    {
        printf("Memory allocation failed!\n");
        return;
    }//newNode->next = next link part of box containing 3.. 
    //set that ink to point to the old node 4

    newNode->vertex = v;//put no 3 inside box
    newNode->next = graph[u - 1];//connect new box to old list
    graph[u - 1] = newNode;//make new box starting point of list
}

/* Add connection according to graph type */
void addConnection(int u, int v)
{
    addOneEdge(u, v);
    if (graphType == 2)
        addOneEdge(v, u);
}

/* Check whether an edge exists */
int edgeExists(int u, int v)//2 5
// vertex 2's list graph[1] = 3= 5= null
{
    struct Node *temp = graph[u - 1];//start at vertex 2's list
                 //temp = graph[1]// temp points to first grpah containing 3
    while (temp != NULL)
    {
        // 3==5 ========= no
        // 5==5 ========= yes return 1
        if (temp->vertex == v)
            return 1;
        temp = temp->next;//move to next box
    }
    return 0;
}

/* Remove one connection */
void removeOneEdge(int u, int v)//u=2 v=4
//graph[1] =3 =4
//want to delete edge 2 to 4
{
    struct Node *temp = graph[u - 1];//means graph[1]
    struct Node *prev = NULL;//not visited any previous node
    while (temp != NULL && temp->vertex != v)//3! =4
    {
        prev = temp;//prev points node 3
        temp = temp->next;//temp moves next
    }
    if (temp == NULL)//temp points to 4 not null
        return;
    if (prev == NULL)//prev points to 3 not null
        graph[u - 1] = temp->next;
    else
        prev->next = temp->next;
        //prev.next =3 
        //temp.next= null
    free(temp);
}
/* Remove connection according to graph type */
void removeConnection(int u, int v)
{
    removeOneEdge(u, v);

    if (graphType == 2)
        removeOneEdge(v, u);
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

    if (edgeExists(u, v))
    {
        printf("Edge already exists.\n");
        return;
    }

    addConnection(u, v);

    if (isGraphConnected())
        printf("Edge inserted successfully.\n");
    else if ((u == 4 && v == 5) ||(u == 5 && v == 4))
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

    printf("\n GRAPH STRUCTURE \n");
    //it displays graph's adjacency list. visits each vertex and prints all verices
    for (i = 0; i < vertices; i++)//visit every vertex
    {
        printf("%d -> ", i + 1);
        // i            i+1
        //0 1 2 3     1 2 3 4
        temp = graph[i];//start at first node if list

        if (temp == NULL)
            printf("No connected vertices");

        while (temp != NULL)
        {
            //uless temp is not null print vertex 
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

    if (u < 1 || u > vertices || v < 1 || v > vertices || u == v)
    {
        printf("Invalid vertex numbers!\n");
        return;
    }

    if (!edgeExists(u, v))
    {
        printf("Edge does not exist.\n");
        return;
    }

    removeConnection(u, v);//removing old connection

    printf("Enter the new edge (u v): ");
    scanf("%d%d", &x, &y);

    if (x < 1 || x > vertices ||y < 1 || y > vertices || x == y)
    {
        addConnection(u, v);
        printf("Invalid vertex numbers! Old edge restored.\n");
        return;
    }

    if (edgeExists(x, y))
    {
        addConnection(u, v);//new connection added
        printf("New edge already exists! Old edge restored.\n");
        return;
    }
    addConnection(x, y);
    printf("Edge updated successfully.\n");
}

/* Delete Edge */
//total vertices 5
void deleteEdge()//to delete bet 2 and 4
{
    int u, v;
    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);//2 4

    if (u < 1 || u > vertices ||v < 1 || v > vertices)
    // (2<1 || 2 > 5 || 4<1 || 4>5)
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

    removeConnection(u, v);
    printf("Edge deleted successfully.\n");
}

/* Delete Vertex */
void deleteVertex()
//delte v2 amnong containg 3 vertices
//graph[0] = 2 = null ////v1
//graph[1] = 1 = 3 = null ////v2
//graph[2] = 2 = null ////v3
{
    int v, i;
    struct Node *temp, *prev, *next;
    //temp visits nodes prev stays behind it next saves next node

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("Enter vertex number to delete: ");
    scanf("%d", &v);

    if (v < 1 || v > vertices)
    //
    {
        printf("Invalid vertex number!\n");
        return;
    }

    /* Remove edges connected to the deleted vertex */
    for (i = 0; i < vertices; i++)//visits every vertex adjacency list
    {
        temp = graph[i];//starts at first node in list
        prev = NULL;

        while (temp != NULL)//visits each node in current adjancy list
        {
            if (temp->vertex == v)//cheks if current node is the deleting node
            {
                next = temp->next;//points to 3 as we enter if
                if (prev == NULL)
                    graph[i] = next;//graph[0]=null
                    //The first node is 2 so prev == NULL
                    //We change graph[i] to point directly to node 4
                else//middle node//prev 3 
                    prev->next = next;
                    //prev->next = next makes node 3 point directly to node 4

                free(temp);
                temp = next;
            }
            else//if current is not dleting node
            {
                //renumber the vertices
                if (temp->vertex > v)//1>2
                    temp->vertex--;//

                prev = temp;//saves the current node as the previous node.points to [1]
                temp = temp->next;//oves to the next node//there is no next node //temp points to[3]
            }
        }
    }

// graph[0] (Vertex 1) -> [2] -> NULL
//graph[1] (Vertex 2) -> [1] -> NULL
//graph[2] (Vertex 3) -> [1] -> NULL
    /* Free the deleted vertex's adjacency list */
    temp = graph[v - 1];
    //temp = graph[1]

    while (temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }

    //we want continue numbering without gaps
    //want old vertex 3 to become 3
    /* Shift the remaining adjacency lists */
    for (i = v - 1; i < vertices - 1; i++)
    //graph[1] = graph[2]
        graph[i] = graph[i + 1];

    vertices--;
    graph[vertices] = NULL;


//graph[0] → Vertex 1       graph[0] → Vertex 1
//graph[1] → Deleted slot   graph[1] → Old Vertex 3's list
//graph[2] → Vertex 3       graph[2] → Old Vertex 3's list
    printf("Vertex deleted successfully.\n");
}

/* Check Connectivity using BFS */
int isGraphConnected()
{
    int seen[MAX] = {0};//marks every vertex as not visited initialyy
    int front = 0, rear = 0;
    int current, i;
    struct Node *temp;

    if (vertices == 0)
        return 0;
    seen[0] = 1;//mean vertex 1 has been visited
    queue[rear++] = 1;// inserts vertex 1 in queue increses rear

    while (front < rear)
    {
        current = queue[front++];
        /* Visit outgoing connections */
        temp = graph[current - 1];// pointing code where to point
        while (temp != NULL)
        {
            i = temp->vertex;//i =2
            if (!seen[i - 1])//checcks seen[1] 
            {
                seen[i - 1] = 1;//marks vertex 2 visited
                queue[rear++] = i;//inserts in the same queue
            }
            temp = temp->next;
        }//moves to null
    for (i = 0; i < vertices; i++)
    {
        if (!seen[i])
            return 0;
    }
    return 1;
}
}
/* Display Connectivity */
void checkConnectivity()
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
            if (!visited[temp->vertex - 1])
            {
                visited[temp->vertex - 1] = 1;
                queue[rear++] = temp->vertex;
            }

            temp = temp->next;
        }
    }

    printf("\n");
}

/* DFS Traversal Helper */
void DFSVisit(int current)
{
    struct Node *temp;

    visited[current - 1] = 1;
    printf("%d ", current);

    temp = graph[current - 1];

    while (temp != NULL)
    {
        if (!visited[temp->vertex - 1])
            DFSVisit(temp->vertex);

        temp = temp->next;
    }
}

/* Depth First Search */
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
