#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(int value)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
struct Node* insertNode(struct Node *root, int value)
{
    struct Node *newNode;
    struct Node *current;
    struct Node *parent;

    newNode = createNode(value);

    if (root == NULL)
    {
        return newNode;
    }
    current = root;
    parent = NULL;
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
            return root;
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

    printf("Node inserted!\n");

    return root;
}
void displayTree(struct Node *root)
{
    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;
    struct Node *current;
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return;
    }

    printf("\n===== TREE STRUCTURE =====\n");
    printf("Root: %d\n", root->data);
    queue[rear++] = root;
    while (front < rear)
    {
        current = queue[front++];

        if (current->left != NULL)
        {
            printf("  Left of %d: %d\n",
                   current->data,
                   current->left->data);

            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            printf("  Right of %d: %d\n",
                   current->data,
                   current->right->data);

            queue[rear++] = current->right;
        }
    }
}
void searchNode(struct Node *root, int value)
{
    struct Node *current = root;
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
void inorder(struct Node *root)
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
void preorder(struct Node *root)
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
void postorder(struct Node *root)
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
struct Node* updateNode(struct Node *root)
{
    int oldValue;
    int newValue;

    printf("Enter old value: ");
    scanf("%d", &oldValue);

    printf("Enter new value: ");
    scanf("%d", &newValue);
    struct Node *current = root;
    while (current != NULL)
    {
        if (current->data == oldValue)
        {
            root = deleteNode(root, oldValue);
            root = insertNode(root, newValue);
            printf("Value updated!\n");
            return root;
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
    return root;
}

struct Node* deleteNode(struct Node *root, int value)
{
    struct Node *current = root;
    struct Node *parent = NULL;
    struct Node *successor;
    struct Node *successorParent;
    struct Node *child;
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
        return root;
    }
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
    if (current->left != NULL)
    {
        child = current->left;
    }
    else
    {
        child = current->right;
    }

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

    printf("Node deleted!\n");

    return root;
}


int main()
{
    struct Node *root = NULL;

    int value;
    int choice;
    char extra;
    printf("Enter root value: ");
    scanf("%d", &value);
    root = createNode(value);
    while (1)
    {
        printf("\n\n===== BINARY SEARCH TREE CRUD =====\n");
        printf("1. Insert\n");
        printf("2. Read\n");
        printf("3. Search\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        if (scanf("%d%c", &choice, &extra) != 2 ||
            extra != '\n')
        {
            printf("Invalid input! Enter digits only.\n");

            while (getchar() != '\n');

            continue;
        }
        if (choice < 1 || choice > 6)
        {
            printf("Invalid choice! Enter 1 to 6.\n");

            continue;
        }

        
        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                displayTree(root);
                printf("\nInorder: ");
                inorder(root);

                printf("\nPreorder: ");
                preorder(root);

                printf("\nPostorder: ");
                postorder(root);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                searchNode(root, value);
                break;
            case 4:
                root = updateNode(root);
                break;
            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 6:
                printf("Program ended.\n");
                exit(0);
        }
    }
    return 0;
}