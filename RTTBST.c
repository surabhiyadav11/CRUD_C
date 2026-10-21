#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int rightThread; 
     // 0 = no thread. point to real child or may be null
    // 1 = thread, thread pointing to IS not real child
};
struct Node *root = NULL;
struct Node* createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1); // Stops the program because node could not be created
    }
    newNode->data = value;
    newNode->left = NULL;  // Initially, left pointer is NULL
    newNode->right = NULL; // Initially, right pointer is NULL
    newNode->rightThread = 0; // Initially, no thread
    return newNode;
}
void insertNode(int value)
{
    // 0 = no thread, 1 = thread
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
        else if (current->rightThread == 0 && current->right != NULL)//null != null (FALSE)
        //50.rightthread==1 && 50.right != null
        //false && true = false
            // No thread, and the right pointer is a real right child
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
        // New node's right pointer is threaded to its inorder successor i.eee 50
        newNode->rightThread = 1;//50 cha pointer 60 la dila and 50 chi right thread 1 ahe 
        parent->left = newNode;
    }
    else
    {
        // New node receives parent's previous right pointer and flag
        newNode->right = parent->right;
        //60.RIGHT=50.RIGHT(=NULL..BEFORE INSERTION)
        newNode->rightThread = parent->rightThread;
        //60.RIGHTTHREAD = 50.rightthread
        parent->right = newNode;
        //50.right=newnode 60
        // Parent now points to a real right child, so it has no thread
        //node 50 chi right thread = 0 so 60 chi pn 1
        parent->rightThread = 0;
    }
    printf("Node inserted.\n");
    // 1 means thread aahe, real child nahi.
}
struct Node* searchNode(int value)
{
    struct Node *current = root;
    while (current != NULL)
    {
        if (current->data == value)
            return current;

        if (value < current->data)
            current = current->left;
        //If the value is not smaller we try moving right 
        //but only if the right pointer is a real child.
        else if (current->rightThread == 0 && current->right != NULL)//to serach 120
        //       right pointer is not thread && real child actually exists
        //       120 cha pointer 125 la ahe but thread nahiye && current 100 vr ahe so tyacha right child nahoye
            current = current->right; //current = 125
        else
            return NULL; // No real right child to continue searching through
    }
    return NULL;
}
void inorder()
{
    struct Node *current = root;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    // Start from the leftmost node
    while (current->left != NULL)//move left until we reachleftmost
        current = current->left;
    while (current != NULL)//keep going as current is not null
    {
        printf("%d ", current->data);
        if (current->rightThread == 1)
            // Thread exists: follow it to the inorder successor
            current = current->right;//follow its thread 
        else
        {
            // No thread: move to the real right child
            current = current->right;

            // Then move to the leftmost node in that subtree
            while (current != NULL && current->left != NULL)
                current = current->left;
        }
    }
    printf("\n");
}
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
        else if (current->rightThread == 0 && current->right != NULL)
            current = current->right;
        else
            current = NULL;
    }
    if (current == NULL)
    {
        printf("Value not found!\n");
        return;
    }
    // If two real children exist, find inorder successor
    if (current->left != NULL &&
        current->rightThread == 0 && current->right != NULL)
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
    // If left child exists
    if (current->left != NULL)
    {
        child = current->left;
        pred = child;
        // Find the rightmost node in the left subtree
        while (pred->rightThread == 0 && pred->right != NULL)
            pred = pred->right;
        // Update predecessor's thread to the deleted node's successor
        pred->right = current->right;
        pred->rightThread = current->rightThread;
        if (parent == NULL)
            root = child;
        else if (parent->left == current)
            parent->left = child;
        else
            parent->right = child;
    }
    // If a real right child exists
    else if (current->rightThread == 0 && current->right != NULL)
    {
        child = current->right;

        if (parent == NULL)
            root = child;
        else if (parent->left == current)
            parent->left = child;
        else
            parent->right = child;
    }
    // If it is a leaf node
    else
    {
        if (parent == NULL)
            root = NULL;
        else if (parent->left == current)
            parent->left = NULL;
        else
        {
            parent->right = current->right;
            parent->rightThread = 1;
            // Parent's right pointer is now a thread
        }
    }
    free(current);
    printf("Node deleted.\n");
}
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
int main()
{
    int choice, value, oldValue, newValue;
    while (1)
    {
        printf("\n--- RIGHT THREADED BST ---\n");
        printf("1. Insert\n");
        printf("2. Read\n");
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