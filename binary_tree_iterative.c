#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
// ====================================================
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// =====================================================
void insertNode(struct Node *root)
{
    int value;
    int parent;
    int choice;
    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;

    struct Node *current;

    printf("Enter value: ");
    scanf("%d", &value);

    printf("Enter parent value: ");
    scanf("%d", &parent);

    printf("1. Left\n");
    printf("2. Right\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    queue[rear++] = root;
    while (front < rear)
    {
        current = queue[front++];
        if (current->data == parent)
        {
            if (choice == 1)
            {
                if (current->left == NULL)
                {
                    current->left = createNode(value);
                    printf("Node inserted!\n");
                }
                else
                {
                    printf("Left child already exists!\n");
                }
            }
            else if (choice == 2)
            {
                if (current->right == NULL)
                {
                    current->right = createNode(value);
                    printf("Node inserted!\n");
                }
                else
                {
                    printf("Right child already exists!\n");
                }
            }
            return;
        }
        // Putting in queuee
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
    printf("Parent not found!\n");
}
// =====================================================
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
            printf("Left of %d: %d\n",current->data,current->left->data);
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            printf("Right of %d: %d\n",current->data,current->right->data);
            queue[rear++] = current->right;
        }
    }
}
// =====================================================
void searchNode(struct Node *root, int value)
{
    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;
    struct Node *current;
    queue[rear++] = root;
    while (front < rear)
    {
        current = queue[front++];
        if (current->data == value)
        {
            printf("Value found!\n");
            return;
        }
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
    printf("Value not found!\n");
}
// ====================================================
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
// =====================================================
void preorder(struct Node *root)
{
    struct Node *stack[MAX];
    int top = -1;
    struct Node *current;
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
// =====================================================
void postorder(struct Node *root)
{
    struct Node *stack1[MAX];
    struct Node *stack2[MAX];
    int top1 = -1;
    int top2 = -1;
    struct Node *current;
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
// =====================================================
void updateNode(struct Node *root)
{
    int oldValue;
    int newValue;
    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;
    struct Node *current;
    printf("Enter old value: ");
    scanf("%d", &oldValue);

    printf("Enter new value: ");
    scanf("%d", &newValue);

    queue[rear++] = root;
    while (front < rear)
    {
        current = queue[front++];
        if (current->data == oldValue)
        {
            current->data = newValue;
            printf("Value updated!\n");
            return;
        }
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
    printf("Value not found!\n");
}
// ====================================================
void deleteNode(struct Node *root)
{
    int value;
    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;
    struct Node *current;

    printf("Enter value to delete: ");
    scanf("%d", &value);
    queue[rear++] = root;

    while (front < rear)
    {
        current = queue[front++];
        // Check left child
        if (current->left != NULL &&
            current->left->data == value)
        {
            free(current->left);
            current->left = NULL;
            printf("Node deleted!\n");
            return;
        }
        // Check right child
        if (current->right != NULL &&
            current->right->data == value)
        {
            free(current->right);
            current->right = NULL;
            printf("Node deleted!\n");
            return;
        }
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }

        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
    printf("Value not found!\n");
}
// ========================================================================================================
int main()
{
    struct Node *root;
    int value;
    int choice;
    char extra;

    printf("Enter root value: ");
    scanf("%d", &value);
    root = createNode(value);
    while (1)
    {
        printf("\n\n===== BINARY TREE CRUD =====\n");
        printf("1. Insert\n");
        printf("2. Read\n");
        printf("3. Search\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        // =============================================================
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
        // =============================================================================
        switch (choice)
        {
            case 1:
                insertNode(root);
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
                updateNode(root);
                break;
            case 5:
                deleteNode(root);
                break;
            case 6:
                printf("Program ended.\n");
                exit(0);
        }
    }

    return 0;
}