#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int rthread;       
    //if node has real right child then rthread=0
    //if node dont have realchild its just points to its IS the rthread is 1
};
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value; //if value=50 then newNode->data = 50
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rthread = 0;//bcoz initially threaads are not creted yet
    return newNode;
}
struct Node* insertNode(struct Node *root, int value)
{//roooot=50
    if (root == NULL)//no node at current position
        return createNode(value);//cureent position vr node nahoye so make a new node and sends its
    if (value < root->data)//insert 30 so //30<50==go left
    {
        //left position la jaun valuse insert kar
        root->left = insertNode(root->left, value);
        //50 ke left child ka pointer = insert(that value will store in roo->left)
    }
    else if (value > root->data)//70>50.... before using right pointer check it is thread or  not
    {
        //0: The right pointer represents a real child pointer 
        //(or NULL if there is no right child) We can safely move through it to insert the node.
        
        //1: The right pointer represents a thread to the inorder successor
        // not a real child. We must not follow it as if it were a child.
        if (root->rthread == 0)//Check karega ki 50 ka right pointer real child pointer hai ya empty hai thread nahi hai
            root->right = insertNode(root->right, value);
    }
    else
    {
        printf("Value already exists!\n");
    }
    return root;
}
void createThreads(struct Node *root, struct Node **previous)
                //current node//privious node address tracking//pointer to pointer hai bcoz functionprevious ki value update kareel
                //previous=simple language mein inorder mein humne last kaunsa node visit kiya tha
{
    if (root == NULL)
        return;
    createThreads(root->left, previous);
    if (*previous != NULL && (*previous)->right == NULL)
    //pehle koi node visit kiya haii && us previous node ka real right child nahi hai.
    {
        (*previous)->right = root;
        (*previous)->rthread = 1;
    }
    *previous = root;
    if (root->rthread == 0)
        createThreads(root->right, previous);
}
// REMOVE OLD THREADS
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
            current = current->right;
        else
        {
            current = current->right;
            while (current != NULL && current->left != NULL)
                current = current->left;
        }
    }
}
int main()
{
    struct Node *root = NULL;
    struct Node *previous = NULL;
    int choice, value;
    char extra;
    while (1)
    {
        printf("\n\n===== RIGHT THREADED BINARY TREE =====\n");
        printf("1. Insert\n");
        printf("2. Read (Inorder)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n')
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
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid value!\n");
                    while (getchar() != '\n');
                    break;
                }
                clearThreads(root);
                root = insertNode(root, value);
                previous = NULL;
                createThreads(root, &previous);
                printf("Insertion completed!\n");
                break;
            case 2:
                if (root == NULL)
                    printf("Tree is empty!\n");
                else
                {
                    printf("Inorder: ");
                    inorder(root);
                    printf("\n");
                }
                break;
            case 3:
                printf("Program ended.\n");
                exit(0);
        }
    }
    return 0;
}
