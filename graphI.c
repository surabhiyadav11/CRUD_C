#include <stdio.h>
#define MAX 20
int graph[MAX][MAX] = {0};
int vertices = 0;
void createVertex()
{
    if (vertices == MAX)
    {
        printf("Graph is full!\n");
        return;
    }
    vertices++;//increases number of vertices by 1
    printf("Vertex %d added successfully.\n", vertices);
}
void createEdge()
{
    int u, v;
    //need atleast 2 vertices to connect if not 2 then this executes
    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }
    //here v=total vertices number
    //if consider u=2 and v=4
    printf("Enter two vertex numbers (1 to %d): ", vertices);
    scanf("%d%d", &u, &v);
    if (u < 1 || u > vertices || v < 1 || v > vertices)
     //(2<1 || 2 > 4 || 4 < 1 || 4 > 4)all are false
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }
//==1 asks is there alredy an connection present!???
    if (graph[u - 1][v - 1] == 1)//in array index start from 0 so// vertex 2= index 1//vertex 4=index 3
     //(graph[2-1][4-1] == 1)([1][3]==1)//here 
    {
        printf("Edge already exists!\n");
        return;
    }//create connection in both direction
    graph[u - 1][v - 1] = 1;
    graph[v - 1][u - 1] = 1;
    printf("Edge added successfully.\n");
}
void readGraph()
{
    int i, j;
    //i=chooses which vertex we are checking
    //j=checks possible connections of that vertex
    int isolatedVertex = 0;//is a vertex has no edges connected to it
    if (vertices == 0)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }
     
    for (i = 0; i < vertices; i++)//checks every vertex one by one
    {
        int connected = 0;
        for (j = 0; j < vertices; j++)//checks every col
        {
            if (graph[i][j] == 1)//==1 means edge exists between the vertices represented by that row and col
            {
                connected = 1;//mark vertex as connected
                break;
            }
        }
        if (connected == 0)//
        {
            isolatedVertex = 1;
            break;
        }
    }
    if (isolatedVertex == 1)
    {
        printf("No graph exists. All vertices are not connected.\n");
        return;
    }
    printf("\nGraph Representation (Adjacency List):\n\n");
    for (i = 0; i < vertices; i++)
    {
        printf("%d -> ", i + 1);//array index 0
        int found = 0;
        for (j = 0; j < vertices; j++)
        {
            if (graph[i][j] == 1)
            {
                printf("%d ", j + 1);//prints connected vertex number
                found = 1;
            }
        }
        if (found == 0)
            printf("No connections");
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
        printf("Self-loops are not allowed.\n");
        return;
    }
    //=================================================
    if (graph[u - 1][v - 1] == 1)//graph[1][1]..by array indexing
    {
        // Edge exists
        printf("Edge already exists between %d and %d.\n", u, v);
        printf("1. Remove Edge\n");
        printf("Choice: ");
        int choice;
        scanf("%d", &choice);
        //to remove an edge
        if (choice == 1)
        {
            graph[u - 1][v - 1] = 0;
            graph[v - 1][u - 1] = 0;
            printf("Edge removed successfully.\n");
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
    //=========================================================
    else
    {
        // No edge exists, so only addition is possible 
        printf("No edge exists between %d and %d.\n", u, v);
        printf("1. Add Edge\n");
        printf("Choice: ");

        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            graph[u - 1][v - 1] = 1;
            graph[v - 1][u - 1] = 1;
            printf("Edge added successfully.\n");
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}
//=========================================================
void deleteEdge()
{
    int u, v;
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
    if (graph[u - 1][v - 1] == 0)
    {
        printf("No edge exists between %d and %d.\n", u, v);
        return;
    }
    graph[u - 1][v - 1] = 0;
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
    printf("Enter vertex number to delete (1 to %d): ", vertices);
    scanf("%d", &v);
    if (v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }
    v--;
    //Shift rows upward// after deleted vertex upward to fill its place
    for (i = v; i < vertices - 1; i++)
    {
        for (j = 0; j < vertices; j++)
            graph[i][j] = graph[i + 1][j];
    }
    //Shift columns leftward 
    for (j = v; j < vertices - 1; j++)
    {
        for (i = 0; i < vertices - 1; i++)
            graph[i][j] = graph[i][j + 1];
    }
    vertices--;//decreses vertex count
    // Clear unused row and column 
    for (i = 0; i < MAX; i++)
    {
        graph[vertices][i] = 0;
        graph[i][vertices] = 0;
    }
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