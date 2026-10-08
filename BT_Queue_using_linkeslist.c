#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node *root = NULL;

struct QueueNode
{
    struct Node *treeNode;
    struct QueueNode *next;
};
struct QueueNode *front = NULL;
struct QueueNode *rear = NULL;
// ENQUEUE
void enqueue(struct Node *node)
{
    struct QueueNode *newNode; //creates pointer for new node in queue
    newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = node; //Stores the Binary Tree node inside the QueueNod
    newNode->next = NULL;
    if (rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {        rear->next = newNode;
        rear = newNode;
    }
}
// dequeueee
struct Node* dequeue() // removes a node from the front of the queue
{
    struct QueueNode *temp;
    struct Node *node;

    if (front == NULL)
        return NULL;

    temp = front;
    node = temp->treeNode;
    front = front->next;
    if (front == NULL)
        rear = NULL;

    free(temp);
    return node;
}
// CHECK QUEUE EMPTY
int isEmpty()
{
    if (front == NULL)
     return 1;
    return 0;
}
//  CREATE NODE 
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//  INSERT USING QUEUE 
void insertNode(int value)
{
    struct Node *current;
    struct Node *newNode = createNode(value);
    if (root == NULL)
    {
        root = newNode;
        printf("Node inserted successfully.\n");
        return;
    }
    enqueue(root); //We put the root into our Linked List Queue
    while (!isEmpty())
    {
        current = dequeue(); //Take one tree node from the queue.
        if (current->left == NULL)
        {
            current->left = newNode;
            printf("Node inserted successfully.\n");
            return;
        }
        else
        {
            enqueue(current->left);
        }
        if (current->right == NULL)
        {
            current->right = newNode;
            printf("Node inserted successfully.\n");
            return;
        }
        else
        {
            enqueue(current->right);
        }
    }
}
//  DISPLAY TREE 
void displayTree()
{
    struct Node *current;
    if (root == NULL)
    {
        printf("Binary tree is empty.\n");
        return;
    }
    printf("\n========== TREE STRUCTURE ==========\n");
    printf("Root: %d\n", root->data);
    enqueue(root);
    while (!isEmpty())
    {
        current = dequeue();
        if (current->left != NULL)
        {
            printf("Left of %d: %d\n",
                   current->data,
                   current->left->data);

            enqueue(current->left);
        }
        if (current->right != NULL)
        {
            printf("Right of %d: %d\n",
                   current->data,
                   current->right->data);

            enqueue(current->right);
        }
    }
}
// SEARCH USING QUEUE 
void searchNode(int value)
{
    struct Node *current;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    enqueue(root);
    while (!isEmpty())
    {
        current = dequeue();
        if (current->data == value)
        {
            printf("Value found!\n");
            return;
        }
        if (current->left != NULL)
        {
            enqueue(current->left);
        }

        if (current->right != NULL)
        {
            enqueue(current->right);
        }
    }
    printf("Value not found!\n");
}
//  INORDER USING STACK 
void inorder() 
{
    struct Node *stack[MAX];
    int top = -1;
    struct Node *current = root;
    while (current != NULL || top != -1)
    {
        while (current != NULL)  
        {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}
// PREORDER USING STACK =================
void preorder()
{
    struct Node *stack[MAX];
    int top = -1;
    struct Node *current;
    if (root == NULL)
        return;
    stack[++top] = root;
    while (top != -1)
    {
        current = stack[top--];
        printf("%d ", current->data);
        if (current->right != NULL)
        {
            stack[++top] = current->right;
        }

        if (current->left != NULL)
        {
            stack[++top] = current->left;
        }
    }
}

void postorder()
{
    struct Node *stack1[MAX];
    struct Node *stack2[MAX];
    int top1 = -1;
    int top2 = -1;

    struct Node *current;
    if (root == NULL)
        return;

    stack1[++top1] = root;

    while (top1 != -1)
{
         current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL)
        {
            stack1[++top1] = current->left;
        }

        if (current->right != NULL)
        {
            stack1[++top1] = current->right;
        }
    }
    while (top2 != -1)
    {
        current = stack2[top2--];

        printf("%d ", current->data);
    }
}
//  BREADTH TRAVERSAL 
void breadthTraversal()
{
    struct Node *current;
    if (root == NULL)
        return;
    enqueue(root);
    while (!isEmpty())
    {
        current = dequeue();
        printf("%d ", current->data);
        if (current->left != NULL)
        {
            enqueue(current->left);
        }

        if (current->right != NULL)
        {
            enqueue(current->right);
        }
    }
}
//depth traver
void depthTraversal()
{
    struct Node *stack[MAX];
    int top = -1;
    struct Node *current;
    if (root == NULL)
        return;
    stack[++top] = root;
    while (top != -1)
    {
        current = stack[top--];
        printf("%d ", current->data);
        if (current->right != NULL)
        {
            stack[++top] = current->right;
        }
        if (current->left != NULL)
        {
            stack[++top] = current->left;
        }
    }
}
// UPDATE USING QUEUE 
void updateNode(int oldValue, int newValue)
{
    struct Node *current;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    enqueue(root);
    while (!isEmpty())
    {
        current = dequeue();
        if (current->data == oldValue)
        {
            current->data = newValue;
            printf("Value updated successfully.\n");
            return;
        }
        if (current->left != NULL)
        {
            enqueue(current->left);
        }
        if (current->right != NULL)
        {
            enqueue(current->right);
        }
    }
    printf("Value not found!\n");
}
//  DELETE USING QUEUE 
void deleteNode(int value)
{
    struct Node *current;
    struct Node *target = NULL;
    struct Node *deepest = NULL;
    struct Node *parent = NULL;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    enqueue(root);
    while (!isEmpty())
    {
        current = dequeue();
        if (current->data == value)
        {
            target = current;
        }
        if (current->left != NULL)
        {
            parent = current;
            deepest = current->left;

            enqueue(current->left);
        }
        if (current->right != NULL)
        {
            parent = current;
            deepest = current->right;
            enqueue(current->right);
        }
    }
    if (target == NULL)
    {
        printf("Value not found!\n");
        return;
    }
    if (deepest == NULL)
    {
        free(root);
        root = NULL;
        printf("Node deleted successfully.\n");
        return;
    }
    target->data = deepest->data;
    if (parent->right == deepest)
    {
        parent->right = NULL;
    }
    else
    {
        parent->left = NULL;
    }
    free(deepest);
    printf("Node deleted successfully.\n");
}
// ================= MAIN =================
int main()
{
    int choice;
    int value;
    int oldValue;
    int newValue;
    while (1)
    {
        printf("\n\n========== BINARY TREE MENU ==========\n");
        printf("1. Create / Insert\n");
        printf("2. Read / Display\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");
        printf("6. Search Using Queue\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertNode(value);
                break;
            case 2:
                if (root == NULL)
                {
                    printf("Binary tree is empty.\n");
                }
                else
                {
                    displayTree();
                    printf("\nInorder: ");
                    inorder();

                    printf("\nPreorder: ");
                    preorder();

                    printf("\nPostorder: ");
                    postorder();

                    printf("\nBreadth Traversal: ");
                    breadthTraversal();

                    printf("\nDepth Traversal: ");
                    depthTraversal();
                    printf("\n");
                }
                break;
            case 3:
                printf("Enter old value: ");
                scanf("%d", &oldValue);

                printf("Enter new value: ");
                scanf("%d", &newValue);
                updateNode(oldValue, newValue);
                break;
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteNode(value);
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);
                searchNode(value);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}