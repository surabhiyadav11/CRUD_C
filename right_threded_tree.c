
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int rthread;               // 0 = right child, 1 = right thread
};
// CREATE NODE
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rthread = 0;

    return newNode;
}

// INSERT NODE
struct Node* insertNode(struct Node *root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
    {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->data)
    {
        if (root->rthread == 1)
        {
            struct Node *newNode = createNode(value);
            newNode->right = root->right;
            newNode->rthread = 1;
            root->right = newNode;
            root->rthread = 0;
        }
        else
        {
            root->right = insertNode(root->right, value);
        }
    }
    else
    {
        printf("Value already exists!\n");
    }

    return root;
}

// CREATE RIGHT THREADS
void createThreads(struct Node *root, struct Node **previous)
{
    if (root == NULL)
        return;

    createThreads(root->left, previous);

    if (*previous != NULL && (*previous)->right == NULL)
    {
        (*previous)->right = root;
        (*previous)->rthread = 1;
    }

    *previous = root;

    if (root->rthread == 0)
        createThreads(root->right, previous);
}

// CLEAR OLD RIGHT THREADS
void clearThreads(struct Node *root)
{
    if (root == NULL)
        return;

    clearThreads(root->left);

    if (root->rthread == 1)
    {
        root->right = NULL;
        root->rthread = 0;
    }
    else
    {
        clearThreads(root->right);
    }
}

// INORDER TRAVERSAL
void inorder(struct Node *root)
{
    struct Node *current = root;

    if (current == NULL)
        return;

    while (current->left != NULL)
        current = current->left;

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

            while (current != NULL && current->left != NULL)
                current = current->left;
        }
    }
}

// PREORDER TRAVERSAL
void preorder(struct Node *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);

    preorder(root->left);

    if (root->rthread == 0)
        preorder(root->right);
}

// POSTORDER TRAVERSAL
void postorder(struct Node *root)
{
    if (root == NULL)
        return;

    postorder(root->left);

    if (root->rthread == 0)
        postorder(root->right);

    printf("%d ", root->data);
}

// MAIN FUNCTION
int main()
{
    struct Node *root = NULL;
    struct Node *previous;
    int choice, value;
    char extra;
    while (1)
    {
        printf("\n\n===== RIGHT-THREADED BINARY TREE =====\n");
        printf("1. Insert\n");
        printf("2. Read (Inorder)\n");
        printf("3. Preorder\n");
        printf("4. Postorder\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n')
        {
            printf("Invalid input! Enter digits only.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice < 1 || choice > 5)
        {
            printf("Invalid choice! Enter 1 to 5.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                printf("Enter value: ");

                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid value!\n");
                    while (getchar() != '\n');
                    break;
                }

                root = insertNode(root, value);

                clearThreads(root);
                previous = NULL;
                createThreads(root, &previous);

                printf("Node inserted!\n");
                break;

            case 2:
                if (root == NULL)
                    printf("Tree is empty!\n");
                else
                {
                    printf("Inorder Traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 3:
                if (root == NULL)
                    printf("Tree is empty!\n");
                else
                {
                    printf("Preorder Traversal: ");
                    preorder(root);
                    printf("\n");
                }
                break;

            case 4:
                if (root == NULL)
                    printf("Tree is empty!\n");
                else
                {
                    printf("Postorder Traversal: ");
                    postorder(root);
                    printf("\n");
                }
                break;

            case 5:
                printf("Program ended.\n");
                exit(0);
        }
    }

    return 0;
}
