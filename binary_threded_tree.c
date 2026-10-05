#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int lthread;
    int rthread;
};
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->lthread = 0;
    newNode->rthread = 0;

    return newNode;
}
struct Node* insertNode(struct Node *root, int value)
{
    struct Node *newNode;
    if (root == NULL)
    {
        return createNode(value);
    }
    if (value < root->data)
    {
        if (root->lthread == 0)
        {
            root->left = insertNode(root->left, value);
        }
    }
    else
    {
        if (root->rthread == 0)
        {
            root->right = insertNode(root->right, value);
        }
    }
    return root;
}
void createThreads(struct Node *root, struct Node **previous)
{
    if (root == NULL)
        return;
    if (root->lthread == 0)
        createThreads(root->left, previous);
    if (root->left == NULL)
    {
        root->left = *previous;
        root->lthread = 1;
    }
    if (*previous != NULL && (*previous)->right == NULL)
    {
        (*previous)->right = root;
        (*previous)->rthread = 1;
    }
    *previous = root;
    if (root->rthread == 0)
        createThreads(root->right, previous);
}
void inorder(struct Node *root)
{
    struct Node *current;
    if (root == NULL)
        return;
    current = root;
    while (current->lthread == 0)
    {
        current = current->left;
    }
    while (current != NULL)
    {
        printf("%d ", current->data);
        if (current->rthread == 1)
        {
            current = current->right;
        }
        else
        {
            current = current->right;
            while (current != NULL && current->lthread == 0)
            {
                current = current->left;
            }
        }
    }
}
void displayTree(struct Node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return;
    }
    printf("\n===== THREADED BINARY TREE =====\n");
    printf("Inorder: ");
    inorder(root);
    printf("\n");
}

int main()
{
    struct Node *root = NULL;
    struct Node *previous = NULL;

    int choice;
    int value;
    char extra;

    while (1)
    {
        printf("\n\n===== THREADED BINARY TREE =====\n");

        printf("1. Insert\n");
        printf("2. Read\n");
        printf("3. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d%c", &choice, &extra) != 2 ||
            extra != '\n')
        {
            printf("Invalid input! Enter digits only.\n");
            while (getchar() != '\n');
            continue;
        }
        if (choice < 1 || choice > 3)
        {
            printf("Invalid choice! Enter 1 to 3.\n");
            continue;
        }
        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                previous = NULL;
                createThreads(root, &previous);
                printf("Node inserted!\n");
                break;
            case 2:
                displayTree(root);
                break;
            case 3:
                printf("Program ended.\n");
                exit(0);
        }
    }
    return 0;
}