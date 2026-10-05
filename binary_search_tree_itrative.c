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
// =======================================================================================================
// CREATE NODE
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
// ==========================================================================================================
// INSERT USING BST RULE
void insertNode(int value)
{
    struct Node *newNode = createNode(value);
    struct Node *current;
    struct Node *parent = NULL;
    if (root == NULL)
    {
        root = newNode;
        printf("Node inserted successfully.\n");
        return;
    }
    
    current = root;
    while (current != NULL)
    {
        parent = current;
        if (value < current->data)
        {
            current = current->left;
        }
        else if (value > current->data)
        {
            current = current->right;
        }
        else
        {
            printf("Value already exists!\n");
            free(newNode);
            return;
        }
    }
    if (value < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    printf("Node inserted successfully.\n");
}
// ====================================================
// DISPLAY TREE STRUCTURE
void displayTree()
{
    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;
    struct Node *current;
    if (root == NULL)
    {
        printf("Binary search tree is empty.\n");
        return;
    }

    printf("\n========== TREE STRUCTURE ==========\n");
    printf("Root: %d\n", root->data);
    queue[rear++] = root;
    while (front < rear)
    {
        current = queue[front++];
        if (current->left != NULL)
        {
            printf("Left of %d: %d\n",
                   current->data,
                   current->left->data);
            queue[rear++] = current->left;
        }

        if (current->right != NULL)
        {
            printf("Right of %d: %d\n",
                   current->data,
                   current->right->data);

            queue[rear++] = current->right;
        }
    }
}
// ====================================================
// SEARCH USING BST
void searchNode(int value)
{
    struct Node *current = root;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    while (current != NULL)
    {
        if (current->data == value)
        {
            printf("Value found!\n");
            return;
        }
        if (value < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    printf("Value not found!\n");
}
// ====================================================
// INORDER USING STACK
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
// ====================================================
// PREORDER USING STACK
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
// ====================================================
// POSTORDER USING 2 STACKS
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
// ====================================================
// BREADTH TRAVERSAL USING QUEUE
void breadthTraversal()
{
    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;
    struct Node *current;
    if (root == NULL)
        return;

    queue[rear++] = root;
    while (front < rear)
    {
        current = queue[front++];
        printf("%d ", current->data);
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
}
// ====================================================
// DEPTH TRAVERSAL USING ssTACK
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
// ====================================================
// UPDATE USING BST
void updateNode(int oldValue, int newValue)
{
    struct Node *current = root;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    while (current != NULL)
    {
        if (current->data == oldValue)
        {
            current->data = newValue;
            printf("Value updated successfully.\n");
            return;
        }

        if (oldValue < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    printf("Value not found!\n");
}
// ====================================================
// DELETE USING BST
void deleteNode(int value)
{
    struct Node *current = root;
    struct Node *parent = NULL;
    struct Node *successor;
    struct Node *successorParent;
    struct Node *child;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    while (current != NULL && current->data != value)
    {
        parent = current;
        if (value < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    if (current == NULL)
    {
        printf("Value not found!\n");
        return;
    }
    // =======================================
    if (current->left != NULL && current->right != NULL)
    {
        successorParent = current;
        successor = current->right;
        while (successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
        }
        current->data = successor->data;
        current = successor;
        parent = successorParent;
    }
    // =======
    if (current->left != NULL)
    {
        child = current->left;
    }
    else
    {
        child = current->right;
    }
    // =======
    if (parent == NULL)
    {
        free(current);
        root = child;
    }
    else if (parent->left == current)
    {
        parent->left = child;
        free(current);
    }
    else
    {
        parent->right = child;
        free(current);
    }
    printf("Node deleted successfully.\n");
}
// ====================================================
// MAIN
int main()
{
    int choice;
    int value;
    int oldValue;
    int newValue;
    while (1)
    {
        printf("\n\n========== BINARY SEARCH TREE MENU ==========\n");
        printf("1. Create / Insert\n");
        printf("2. Read / Display\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");
        printf("6. Search\n");
        printf("=============================================\n");
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
                    printf("Binary search tree is empty.\n");
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