#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct Node
{
    int vertex;
    struct Node *next;
};
struct Node *adj[MAX];
int visited[MAX];
int queue[MAX];
int n;
// Add one edge to adjacency list
void addOneEdge(int u, int v)//2,5 //u=2 v=5
{
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->vertex = v;//vertex v =5
    newNode->next = adj[u];//connect it to old list
    adj[u] = newNode;//make it first node in the list// old node will eemain same//[] = newnode ->oldnode ->null
    //Make the new node the first node in the list
}
void addEdge(int u, int v, int type)
{
    addOneEdge(u, v);//one direction forward
    // Undirected graph: add reverse edge
    if (type == 2)
        addOneEdge(v, u);//another direction again backward
}
void BFS(int start)
{
    int front = 0, rear = 0;//initialise queue
    for (int i = 0; i < n; i++)
        visited[i] = 0;//all vertices are unvisited

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS: ");
    while (front < rear)
    {
        int current = queue[front++];
        printf("%d ", current);
        // Check vertices from smallest to largest
        for (int v = 0; v < n; v++)//cheks vertices in numerical order
        {
            struct Node *temp = adj[current];// 0 1 and 0 2 inserted in adjancy list
            while (temp != NULL)//temp travels thorh adjacency list of current vertex
            {
                //checks whether v is connected to current and not visited
                if (temp->vertex == v && visited[v] == 0)
                {
                    visited[v] = 1;//if both true comes in and marks it as 1
                    queue[rear++] = v;
                    break;
                }
                temp = temp->next;//moves to next node in list
            }
        }
    }
    printf("\n");
}
void DFS(int current)
{
    visited[current] = 1;//current = 0
    printf("%d ", current);//prints 0
    for (int v = 0; v < n; v++)
    {
        //as current=0 temp starts at beging of adj[0] 
        struct Node *temp = adj[current];
        while (temp != NULL)
        {
            if (temp->vertex == v && visited[v] == 0)//looks for connected vertex that has not visited
            {
                DFS(v);//again calls function
                break;
            }
            temp = temp->next;
        }
    }
}
int main()
{
    int edges, u, v, start, type, choice;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of vertices!\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
        adj[i] = NULL;
    //initially every vertex has an empty adjacency list

    printf("\n1. Directed Graph\n");
    printf("2. Undirected Graph\n");
    printf("Enter graph type: ");
    scanf("%d", &type);

    if (type != 1 && type != 2)
    {
        printf("Invalid graph type!\n");
        return 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    if (edges < 0 || edges>n*(n - 1))
    {
        printf("Invalid number of edges!\n");
        return 0;
    }
    printf("Enter each edge as two vertices (u v)\n");
    printf("Vertices must be from 0 to %d\n", n - 1);
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid vertex!\n");
            return 0;
        }

        addEdge(u, v, type);
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    if (start < 0 || start >= n)
    {
        printf("Invalid starting vertex!\n");
        return 0;
    }

    printf("\n1. BFS\n");
    printf("2. DFS\n");
    printf("Enter traversal choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        BFS(start);
    }
    else if (choice == 2)
    {
        for (int i = 0; i < n; i++)
            visited[i] = 0;

        printf("DFS: ");
        DFS(start);
        printf("\n");
    }
    else
    {
        printf("Invalid choice!\n");
    }

    return 0;
}
