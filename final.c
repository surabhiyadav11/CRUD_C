#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int rightThread;  //// // 1 = thread 0 = real right child
};
struct Node *root = NULL;
struct Node* createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);//stops the program bcoz node could not be created
    }
    newNode->data = value;
    newNode->left = NULL;//initially left is null obiviously
    newNode->right = NULL;//initially right is null obiviouly
    newNode->rightThread = 1;//initially its right pointer is a threaddd
    return newNode;
}
void insertNode(int value)
{
    struct Node *current = root;//initially current = root = 70
    struct Node *parent = NULL;
    struct Node *newNode;
    while (current != NULL)// joparynt current ha null nahi hota
    {
        if (value == current->data)//60 == 70??? not go in loop
        {
            printf("Value already exists!\n");
            return;
        }
        parent = current; //70 = parentt 
        if (value < current->data)
            current = current->left;
        else if (current->rightThread == 0)//will not execute to insert 80 bocz 80 is not inserted yet
        //current jela point karat ahe tech pointer real child ahe ka
        //node 70 has no real child yet thread is 1
            current = current->right;
        else
            break;
    }
    newNode = createNode(value);
    if (parent == NULL)
        root = newNode;
    else if (value < parent->data)
    {
        newNode->right = parent;//60 ch right pointer 70 la thread karnar 
        //60 ch right thred 70 la pointer karnar... 70 ch left pointer 60 la point karnar
        parent->left = newNode;
    }
    else
    {
        newNode->right = parent->right; 
        //parent=70 //parent.right=null//70 cha right pointer thread ahe
        //80 cha right pointer 70 chya right pointer to recive karnar
        parent->right = newNode;
        //70 cha right pointer 80 cha address save karato
        parent->rightThread = 0;
        //ata 80 insert zala tr 70 cha right pointer is not thread anymore ata toh real right child la point karel 
    }
    printf("Node inserted.\n");
}
struct Node* searchNode(int value)
{
    struct Node *current = root;
    while (current != NULL)//jparynt current null nahi hota
    {
        if (current->data == value)
            return current;
        if (value < current->data)
            current = current->left;
            //value>than current node//check wheather its right pointer points to real child
        else if (current->rightThread == 0)
        //0 real child 1 real thread
        //to search 85 70's rightthread=0.(as has real child)
        //means right pointer is real child
            current = current->right;//move to that child
        else
            return NULL;//if right pointer null asel tar
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
    while (current->left != NULL)
        current = current->left;
    while (current != NULL)
    {
        printf("%d ", current->data);
        if (current->rightThread == 1)
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
        else if (current->rightThread == 0)
            current = current->right;
        else
            current = NULL;
    }
    if (current == NULL)
    {
        printf("Value not found!\n");
        return;
    }
    // If two children exist, find inorder successor
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
        while (pred->rightThread == 0 && pred->right != NULL)
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
    // If real right child exists
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
    if (searchNode(oldValue) == NULL)//search for old value 
    //call directly search function
    {
        printf("Value not found!\n");
        return;
    }
    if (searchNode(newValue) != NULL)//want to insert 80 but its alredy present 
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
        printf("2. Read \n");
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
