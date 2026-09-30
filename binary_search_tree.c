#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
// =====================================================
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
struct Node* insertNode(struct Node *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->data)
    {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insertNode(root->right, value);
    }
    else
    {
        printf("Value already exists!\n");
    }

    return root;
}
// =====================================================
void inorder(struct Node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
void preorder(struct Node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
void postorder(struct Node *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}
// ====================================================================
struct Node* updateNode(struct Node *root, int oldValue, int newValue)
{
    if (root == NULL)
    {
        printf("Value not found!\n");
        return root;
    }
    if (oldValue < root->data)
    {
        root->left = updateNode(root->left, oldValue, newValue);
    }
    else if (oldValue > root->data)
    {
        root->right = updateNode(root->right, oldValue, newValue);
    }
    else
    {
        root->data = newValue;
        printf("Value updated!\n");
    }
    return root;
}
// =====================================================
struct Node* findMin(struct Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
// =====================================================
struct Node* deleteNode(struct Node *root, int value)
{
    if (root == NULL)
    {
        printf("Value not found!\n");
        return root;
    }

    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }

    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }

    else
    {
        // No child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // Only right child
        else if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        // Only left child
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        // Two children
        else
        {
            struct Node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}
// =====================================================
int main()
{
    struct Node *root = NULL;
    int choice;
    int value;
    int oldValue;
    int newValue;
    char extra;
    while (1)
    {
        printf("\n\n===== BINARY SEARCH TREE CRUD =====\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        // =================================================
        if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n')
        {
            printf("Invalid input! Please enter digits only.\n");
            while (getchar() != '\n');
            continue;
        }
        if (choice < 1 || choice > 5)
        {
            printf("Invalid choice! Please enter 1 to 5.\n");
            continue;
        }
        // =================================================
        switch (choice)
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("Node created successfully!\n");
                break;            
            case 2:
                if (root == NULL)
                {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("\nInorder: ");
                inorder(root);

                printf("\nPreorder: ");
                preorder(root);

                printf("\nPostorder: ");
                postorder(root);
                break;
            case 3:
                printf("Enter old value: ");
                scanf("%d", &oldValue);

                printf("Enter new value: ");
                scanf("%d", &newValue);
                root = updateNode(root, oldValue, newValue);
                break;
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 5:
                printf("Program ended.\n");
                exit(0);
        }
    }
    return 0;
}