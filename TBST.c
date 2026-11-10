
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int rightThread;   // 0 = thread, 1 = real right child
};

struct Node *root = NULL;

// CREATE NODE
struct Node* createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rightThread = 0;

    return newNode;
}

// INSERT NODE
void insertNode(int value)
{
    struct Node *current = root;
    struct Node *parent = NULL;
    struct Node *newNode;

    while (current != NULL)
    {
        if (value == current->data)
        {
            printf("Value already exists!\n");
            return;
        }

        parent = current;

        if (value < current->data)
            current = current->left;
        else if (current->rightThread == 1)
            current = current->right;
        else
            break;
    }

    newNode = createNode(value);

    if (parent == NULL)
        root = newNode;

    else if (value < parent->data)
    {
        newNode->right = parent;
        parent->left = newNode;
    }
    else
    {
        newNode->right = parent->right;
        parent->right = newNode;
        parent->rightThread = 1;
    }

    printf("Node inserted.\n");
}

// SEARCH NODE
struct Node* searchNode(int value)
{
    struct Node *current = root;

    while (current != NULL)
    {
        if (current->data == value)
            return current;

        if (value < current->data)
            current = current->left;
        else if (current->rightThread == 1)
            current = current->right;
        else
            return NULL;
    }

    return NULL;
}

// INORDER TRAVERSAL
void inorder()
{
    struct Node *current = root;

    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    while (current->left != NULL)
        current = current->left;

    while (current != NULL)
    {
        printf("%d ", current->data);

        if (current->rightThread == 0)
            current = current->right;
        else
        {
            current = current->right;

            while (current != NULL && current->left != NULL)
                current = current->left;
        }
    }

    printf("\n");
}

// DELETE NODE
void deleteNode(int value)
{
    struct Node *current = root;
    struct Node *parent = NULL;
    struct Node *child, *pred, *succ, *succParent;

    while (current != NULL && current->data != value)
    {
        parent = current;

        if (value < current->data)
            current = current->left;
        else if (current->rightThread == 1)
            current = current->right;
        else
            current = NULL;
    }

    if (current == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    // IF TWO CHILDREN EXIST
    if (current->left != NULL &&
        current->rightThread == 1 && current->right != NULL)
    {
        succParent = current;
        succ = current->right;

        while (succ->left != NULL)
        {
            succParent = succ;
            succ = succ->left;
        }

        current->data = succ->data;
        parent = succParent;
        current = succ;
    }

    // IF LEFT CHILD EXISTS
    if (current->left != NULL)
    {
        child = current->left;
        pred = child;

        while (pred->rightThread == 1 && pred->right != NULL)
            pred = pred->right;

        pred->right = current->right;
        pred->rightThread = current->rightThread;

        if (parent == NULL)
            root = child;
        else if (parent->left == current)
            parent->left = child;
        else
            parent->right = child;
    }

    // IF REAL RIGHT CHILD EXISTS
    else if (current->rightThread == 1 && current->right != NULL)
    {
        child = current->right;

        if (parent == NULL)
            root = child;
        else if (parent->left == current)
            parent->left = child;
        else
            parent->right = child;
    }

    // IF LEAF NODE
    else
    {
        if (parent == NULL)
            root = NULL;
        else if (parent->left == current)
            parent->left = NULL;
        else
        {
            parent->right = current->right;
            parent->rightThread = 0;
        }
    }

    free(current);
    printf("Node deleted.\n");
}

// UPDATE NODE
void updateNode(int oldValue, int newValue)
{
    if (oldValue == newValue)
    {
        printf("Both values are same.\n");
        return;
    }

    if (searchNode(oldValue) == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    if (searchNode(newValue) != NULL)
    {
        printf("New value already exists!\n");
        return;
    }

    deleteNode(oldValue);
    insertNode(newValue);

    printf("Value updated.\n");
}

// MAIN FUNCTION
int main()
{
    int choice, value, oldValue, newValue;

    while (1)
    {
        printf("\n--- RIGHT THREADED BST ---\n");
        printf("1. Insert\n");
        printf("2. Read (Inorder)\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Search\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                printf("Enter value: ");

                if (scanf("%d", &value) == 1)
                    insertNode(value);
                else
                {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;

            case 2:
                inorder();
                break;

            case 3:
                printf("Enter old value and new value: ");

                if (scanf("%d%d", &oldValue, &newValue) == 2)
                    updateNode(oldValue, newValue);
                else
                {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;

            case 4:
                printf("Enter value to delete: ");

                if (scanf("%d", &value) == 1)
                    deleteNode(value);
                else
                {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;

            case 5:
                printf("Enter value to search: ");

                if (scanf("%d", &value) == 1)
                {
                    if (searchNode(value) != NULL)
                        printf("Value found!\n");
                    else
                        printf("Value not found!\n");
                }
                else
                {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                }
                break;

            case 6:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}