#include <stdio.h>
#include <stdlib.h>                
#define MAX 100
struct Node
{
    int data;                       // stores value of node
    struct Node *left;              // points to left child
    struct Node *right;             // points to right child
};
struct Node *root = NULL;           // root points to first node
// CREATE NODE 
struct Node* createNode(int value)
{
    struct Node *newNode;            // pointer for new node
    newNode = (struct Node*)malloc(sizeof(struct Node)); 
    newNode->data = value;           // stores value in node
    newNode->left = NULL;            // initially no left child
    newNode->right = NULL;           // initially no right child
    return newNode;                  // returns address of new node
}
//  INSERT USING BST RULE 
void insertNode(int value)
{
    struct Node *newNode = createNode(value); // creates new node
    struct Node *current;            // points to current node
    struct Node *parent = NULL;       // stores parent of current node
    if (root == NULL)                // jar root=null means apan newnode jo inserrt karat ahot that is root node
    {
        root = newNode;              
        printf("Node inserteddd successfully.\n");
        return;                     
    }
    current = root;                   // starts checking from root
    while (current != NULL)           // continues until empty position is found
    {
        parent = current;             // stores current node as paren
        if (value < current->data)    // checks if value is smaller
        {
            current = current->left;  // moves to left child
        }
        else if (value > current->data) // checks if value is greater
        {
            current = current->right; // moves to right child
        }
        else                           // value is equal
        {
            printf("Value already exists!\n");
            free(newNode);             // deletes unused new node from memory
            return;                    // stops function
        }
    }
    if (value < parent->data)          // checks if value belongs on left
    {
        parent->left = newNode;        // connects new node as left child
    }
    else
    {
        parent->right = newNode;       // connects new node as right child
    }
    printf("Node inserted successfully.\n");
}
//  SEARCH USING BST 
void searchNode(int value)
{
    struct Node *current = root;       // starts searching from root
    if (root == NULL)                  // checks if tree is empty
    {
        printf("Tree is empty.\n");
        return;                        // stops function
    }
    while (current != NULL)            // continues until node is found/not found
    {
        if (current->data == value)    // checks current node value
        {
            printf("Value found!\n");
            return;                    // stops when value is found
        }
        if (value < current->data)     // checks if value is smaller
        {
            current = current->left;   // moves to left child
        }
        else
        {
            current = current->right;  // moves to right child
        }
    }
    printf("Value not found!\n");       // value does not exist
}
// INORDER USING STACK 
void inorder()
{
    struct Node *stack[MAX];            // stack stores node addresses
    int top = -1;                       // stack is initially empty
    struct Node *current = root;        // starts from root
    while (current != NULL || top != -1)
    {
        while (current != NULL)         // moves towards left side
        {
            stack[++top] = current;     // pushes current node into stack
            current = current->left;    // moves to left child
        }
        current = stack[top--];         // pops node from stack
        printf("%d ", current->data);   // prints node value
        current = current->right;       // moves to right child
    }
}
//  PREORDER USING STACK 
void preorder()
{
    struct Node *stack[MAX];            // stack stores node addresses
    int top = -1;                       // stack is initially empty
    struct Node *current;               // points to current nod
    if (root == NULL)                   // checks if tree is empty
        return;                         // stops function
    stack[++top] = root;                // pushes root into stack
    while (top != -1)                   // runs while stack is not empty
    {
        current = stack[top--];         // pops node from stack
        printf("%d ", current->data);   // prints current node
        if (current->right != NULL)     // checks if right child exists
        {
            stack[++top] = current->right; // pushes right child into stack
        }
        if (current->left != NULL)      // checks if left child exists
        {
            stack[++top] = current->left;// pushes left child into stack
        }
    }
}
//POSTORDER USING 2 STACK
void postorder()
{
    struct Node *stack1[MAX];           // first stack
    struct Node *stack2[MAX];           // second stack
    int top1 = -1;                      // Stack 1 is empty
    int top2 = -1;                      // Stack 2 is empty
    struct Node *current;               // points to current node
    if (root == NULL)                   // checks if tree is empty
        return;                         // stops function
    stack1[++top1] = root;              // pushes root into Stack 1
    while (top1 != -1)                  // runs while Stack 1 is not empty
    {
        current = stack1[top1--];      // pops node from Stack 1
        stack2[++top2] = current;      // pushes node into Stack 2
        if (current->left != NULL)      // checks if left child exists
        {
            stack1[++top1] = current->left;   // pushes left child into Stack 1
        }
        if (current->right != NULL)     // checks if right child exists
        {
            stack1[++top1] = current->right;// pushes right child into Stack 1
        }
    }
    while (top2 != -1)// runs while Stack 2 is not empty
    {
        current = stack2[top2--];       // pops node from Stack 2
        printf("%d ", current->data);   // prints node value
    }
}
//  BREADTH TRAVERSAL USING QUEUE 
void breadthTraversal()
{
    struct Node *queue[MAX];            // queue stores node addresses
    int front = 0;                      // points to first queue position
    int rear = 0;                       // points to next empty queue position
    struct Node *current;               // points to current node
    if (root == NULL)                   // checks if tree is empty
        return;                         // stops function
    queue[rear++] = root;               // adds root to queue
    while (front < rear)                // runs while queue has nodes
    {
        current = queue[front++];       // removes node from front
        printf("%d ", current->data);   // prints node value
        if (current->left != NULL)      // checks if left child exists
        {
            queue[rear++] = current->left;// adds left child to queue
        }
        if (current->right != NULL)     // checks if right child exists
        {
            queue[rear++] = current->right;  // adds right child to queue
        }
    }
}
//  DEPTH TRAVERSAL USING STACK 
void depthTraversal()
{
    struct Node *stack[MAX];            // stack stores node addresses
    int top = -1;                       // stack is initially empty
    struct Node *current;               // points to current node
    if (root == NULL)                   // checks if tree is empty
        return;                         // stops function
    stack[++top] = root;                // pushes root into stack
    while (top != -1)                   // runs while stack is not empty
    {
        current = stack[top--];         // pops node from stack
        printf("%d ", current->data);   // prints node value
        if (current->right != NULL)     // checks if right child exists
        {
            stack[++top] = current->right; // pushes right child into stack
        }
        if (current->left != NULL)      // checks if left child exists
        {
            stack[++top] = current->left;  // pushes left child into stack
        }
    }
}

//  UPDATE USING BST 
void updateNode(int oldValue, int newValue)
{
    struct Node *current = root;        // starts from roo
    if (root == NULL)                   // checks if tree is empty
    {
        printf("Tree is empty.\n");
        return;                         // stops function
    }
    while (current != NULL)             // continues while node exists
    {
        if (current->data == oldValue)  // checks if old value is found
        {
            current->data = newValue;   // changes old value to new value
            printf("Value updated successfully.\n");
            return;                     // stops function
        }
        if (oldValue < current->data)   // checks if old value is smaller
        {
            current = current->left;    // moves to left child
        }
        else
        {
            current = current->right;   // moves to right child
        }
    }
    printf("Value not found!\n");        // old value was not found
}
//  DELETE USING BST 

void deleteNode(int value)
{
    struct Node *current = root;         // starts from root
    struct Node *parent = NULL;          // stores parent node
    struct Node *successor;             // stores inorder successor
    struct Node *successorParent;       // stores successor's parent
    struct Node *child;                 // stores child of node to delete
    if (root == NULL)                   // checks if tree is empty
    {
        printf("Tree is empty.\n");
        return;                     
    }
    while (current != NULL && current->data != value) // searches for value 
    {
        parent = current;               // stores current as parent
        if (value < current->data)      // checks if value is smaller
        {
            current = current->left;    // moves to left child
        }
        else
        {
            current = current->right;   // moves to right child
        }
    }
    if (current == NULL)                // checks if value was not found
    {
        printf("Value not found!\n");
        return;                         // stops function
    }
    // NODE HAS TWO CHILDREN =================
    if (current->left != NULL && current->right != NULL) // checks for two children
    {
        successorParent = current;      // stores current as successor parent
        successor = current->right;     // starts successor from right child
        while (successor->left != NULL)  // moves to leftmost node
        {
            successorParent = successor; // updates successor parent
            successor = successor->left; // moves to left child
        }
        current->data = successor->data;              // copies successor value
        current = successor;             // current becomes successor
        parent = successorParent;       // parent becomes successor parent
    }
    //  FIND CHILD 
    if (current->left != NULL)           // checks if left child exists
    {
        child = current->left;           // child points to left child
    }
    else
    {
        child = current->right;          // child points to right child
    }
    //  DELETE NODE
    if (parent == NULL)                  // checks if deleting root
    {
        free(current);                   // deletes current node
        root = child;                    // child becomes new root
    }
    else if (parent->left == current)    // checks if current is left child
    {
        parent->left = child;            // connects parent to child
        free(current);                   // deletes current node
    }
    else
    {
        parent->right = child;           // connects parent to child
        free(current);                   // deletes current node
    }
    printf("Node deleted successfully.\n");
} 
int main()
{
    int choice;                      
    int value;                         
    int oldValue;                        
    int newValue;                        
    while (1)                          
    {
        printf("\n\n========== BINARY SEARCH TREE MENU ==========\n");
        printf("1. Create / Insert\n");  
        printf("2. Traversals\n");      
        printf("3. Update\n");         
        printf("4. Delete\n");           
        printf("5. Exit\n");            
        printf("6. Search\n");          
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);            
        switch (choice)               
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);     
                insertNode(value);      
                break;              
            case 2:
                if (root == NULL)      
                {
                    printf("Binary search tree is empty.\n");
                }
                else
                {
                    printf("\nInorder: ");
                    inorder();          
                    printf("\nPreorder: ");
                    preorder();     
                    printf("\nPostorder: ");
                    postorder();        
                    printf("\nBreadth Traversal: ");
                    breadthTraversal(); 
                    printf("\nDepth Traversal: ");
                    depthTraversal(); 
                    printf("\n");
                }
                break;                  
            case 3:
                printf("Enter old value: ");
                scanf("%d", &oldValue); 
                printf("Enter new value: ");
                scanf("%d", &newValue); 
                updateNode(oldValue, newValue);
                break;                  
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &value);   
                deleteNode(value);      
                break;             
            case 5:
                printf("Exiting program...\n");
                exit(0);                
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value); 
                searchNode(value);    
                break;                  
            default:
                printf("Invalid choice!\n"); 
        }
    }
    return 0;                           
}