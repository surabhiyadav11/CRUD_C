
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

struct Node *root = NULL;

//don numbers madhun motha number return karnar
int max(int a, int b)//a=2 b=3 false
{
    return (a > b) ? a : b;//ternary op if condition true first value otherwise second value
}

// Find height of a node
int height(struct Node *node)
{
    if (node == NULL)
        return 0;

    return node->height;
}

// Calculate balance factor
int balanceFactor(struct Node *node)
{
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

// Create a new node
struct Node *createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Right rotation (LL case)
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *temp = x->right;
    //x points to 20 but 20 cha right child ahe ka? no so temp=null

    x->right = y;
    // x cha ek pointer 10 la point karat ahe ani dusra right pointer 30 la point karat ahe
    //so x cha right pointer andd y he donhi 30 lach point karratat

    //but now temprory 30 cha left ha 20 la point karato we have to break that
    y->left = temp;
    //ata y cha left pointer temp jithe point karato tithe set karu
    // temp null hota apala so y.left=null honal

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Left rotation (RR case)
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *temp = y->left;
    //x->right = temp kelyavar 10 cha right pointer NULL hoto
    //mhanun old connection tutato.

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

struct Node *insertNode(struct Node *node, int value)
{
    if (node == NULL)
        return createNode(value);

    if (value < node->data)
        node->left = insertNode(node->left, value);

    else if (value > node->data)
        node->right = insertNode(node->right, value);

    else
    {
        printf("Duplicate value not allowed!\n");
        return node;
    }

// ===================================================
    // Update height
    node->height = 1 + max(height(node->left), height(node->right));
//===============================================

    // Find balance factor
    int bf = balanceFactor(node);
//========================================================
    // LL case
    //root cha bf
    if (bf > 1 && value < node->left->data)
        return rightRotate(node);

    // RR case
    //bcoz imbalace at right side only
    if (bf < -1 && value > node->right->data)
        return leftRotate(node);

    // LR case
    if (bf > 1 && value > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL case
    if (bf < -1 && value < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(struct Node *node)
{
    if (node == NULL)
        return;

    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function prototype
struct Node *deleteNode(struct Node *node, int value);

struct Node *updateNode(struct Node *node, int oldValue, int newValue)
{
    struct Node *temp = node;

    while (temp != NULL && temp->data != oldValue)
    //pointer reach hota nahi ani old value bhetatt nahi
    {
        if (oldValue < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if (temp == NULL)
    {
        printf("Value not found!\n");
        return node;
    }

    if (oldValue == newValue)
    {
        printf("Old and new values are the same!\n");
        return node;
    }

    temp = node;

    while (temp != NULL && temp->data != newValue)//search for new valuew that alredy exists??
    {
        if (newValue < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if (temp != NULL)
    {
        printf("Duplicate value not allowed!\n");
        return node;
    }

    node = deleteNode(node, oldValue);
    node = insertNode(node, newValue);

    printf("Value updated successfully!\n");
    return node;
}

struct Node *deleteNode(struct Node *node, int value)
{
    if (node == NULL)
        return NULL;

    if (value < node->data)
        node->left = deleteNode(node->left, value);

    else if (value > node->data)
        node->right = deleteNode(node->right, value);

    else//no child or single child
    {
        if (node->left == NULL || node->right == NULL)
        {
            struct Node *temp;

            if (node->left != NULL)
                temp = node->left;
            else
                temp = node->right;

            free(node);
            return temp;
        }

//for replacement of node choose inorder succesor
        struct Node *temp = node->right;

        while (temp->left != NULL)
            temp = temp->left;

        node->data = temp->data;// cppy in 20'splace so two 30
        node->right = deleteNode(node->right, temp->data);
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int bf = balanceFactor(node);

    // LL case
    if (bf > 1 && balanceFactor(node->left) >= 0)
        return rightRotate(node);

    // LR case
    if (bf > 1 && balanceFactor(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RR case
    if (bf < -1 && balanceFactor(node->right) <= 0)
        return leftRotate(node);

    // RL case
    if (bf < -1 && balanceFactor(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n1. Insert");
        printf("\n2. Display");
        printf("\n3. Delete");
        printf("\n4. Update");
        printf("\n5. Exit");
        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 0;
        }

        switch (choice)
        {
            case 1:
                printf("Enter value: ");

                if (scanf("%d", &value) != 1)
                    return 0;

                root = insertNode(root, value);
                break;

            case 2:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                printf("Enter value to delete: ");

                if (scanf("%d", &value) != 1)
                    return 0;

                root = deleteNode(root, value);
                break;

            case 4:
            {
                int oldValue, newValue;

                printf("Enter value to update: ");

                if (scanf("%d", &oldValue) != 1)
                    return 0;

                printf("Enter new value: ");

                if (scanf("%d", &newValue) != 1)
                    return 0;

                root = updateNode(root, oldValue, newValue);
                break;
            }

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
