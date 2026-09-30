#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};
// ===================================================================Create a new node
struct Node* createNode(int value)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
// ================================================================CREATE
void insertNode(struct Node *root)
{
    int value;
    int parentValue;
    int choice;

    printf("Enter value to insert: ");
    scanf("%d", &value);

    printf("Enter parent value: ");
    scanf("%d", &parentValue);

    printf("Where do you want to insert?\n");
    printf("1. Left\n");
    printf("2. Right\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (root->data == parentValue)
    {
        if (choice == 1)
        {
            if (root->left == NULL)
                root->left = createNode(value);
            else
                printf("Left child already exists!\n");
        }

        else if (choice == 2)
        {
            if (root->right == NULL)
                root->right = createNode(value);
            else
                printf("Right child already exists!\n");
        }

        return;
    }

    if (root->left != NULL)
        insertNode(root->left);

    if (root->right != NULL)
        insertNode(root->right);
}


// ===================================================READ 
//  INORDER
void inorder(struct Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}


// READ - PREORDER
void preorder(struct Node *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}


// READ - POSTORDER
void postorder(struct Node *root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}
// =========================================================UPDATE
void updateNode(struct Node *root, int oldValue, int newValue)
{
    if (root == NULL)
        return;

    if (root->data == oldValue)
    {
        root->data = newValue;
        return;
    }

    updateNode(root->left, oldValue, newValue);
    updateNode(root->right, oldValue, newValue);
}
// ===========================================================DELETE
void deleteNode(struct Node *root, int value)
{
    if (root == NULL)
        return;

    if (root->left != NULL &&
        root->left->data == value)
    {
        free(root->left);
        root->left = NULL;
        return;
    }

    if (root->right != NULL &&
        root->right->data == value)
    {
        free(root->right);
        root->right = NULL;
        return;
    }

    deleteNode(root->left, value);
    deleteNode(root->right, value);
}

int main()
{
    struct Node *root;

    int choice;
    int oldValue;
    int newValue;
    int value;
    char extra;
    // Create root node
    printf("Enter root value: ");
    scanf("%d", &value);

    root = createNode(value);
    while (1)
    {
        printf("\n\n===== BINARY TREE CRUD =====\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");


        // ================================================================MENU INPUT VALIDATIONNNNN
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

       // =====================================================================
        switch (choice)
        {
            case 1:
                insertNode(root);
                break;
            case 2:
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

                updateNode(root, oldValue, newValue);

                printf("Value updated!\n");
                break;
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &value);

                deleteNode(root, value);
                printf("Node deleted!\n");
                break;
            case 5:
                printf("Program ended.\n");
                exit(0);
        }
    }
    return 0;
}