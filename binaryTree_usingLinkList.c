#include <stdio.h>
#include <stdlib.h>
#define MAX 100                 // maximum size of stack
// tree node's initi
struct Node
{
    int data;                   // stores the value of the node
    struct Node *left;          // points to the left child
    struct Node *right;         
};
struct Node *root = NULL;       // root points to the first node of tree

// queue's node
struct QueueNode
{
    struct Node *treeNode;      // stores address of a Binary Tree node
    struct QueueNode *next;     // points to the next queue node
};

struct QueueNode *front = NULL; // poiints to first node of queue
struct QueueNode *rear = NULL;  

//enqueueeee
void enqueue(struct Node *node)// adds a tree node to queue
{
    struct QueueNode *newNode;                         // pointer for new queue node
    newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = node;// stores tree node address
    newNode->next = NULL;//new node has no next node
    if (rear == NULL)// checks if queue is empty
    {
        front = rear = newNode;// new node becomes front and rear
    }
    else
    {
        rear->next = newNode;// connects old rear to new node
        rear = newNode;// new node becomes the rear
    }
}

//dequeue
struct Node* dequeue()
{
    struct QueueNode *temp;
    struct Node *node;// stores tree node address
    if (front == NULL)// checks if queue is empty
        return NULL; // returns NULL if empty
    temp = front;// temp points to front queue nodeee  
    node = temp->treeNode;// to get the binarytree address stored inside the queue node
    front = front->next;// moves front to next queue node
    if (front == NULL)// checks if queue became empty
        rear = NULL;// resets rear to NULL
    free(temp);// deletes old queue node from memory
    return node;// returns tree node address
}
//  CHECK QUEUE EMPTY 
int isEmpty()                                          
{
    if (front == NULL)                                 
        return 1;                                    
    return 0; // returns 0 if queue is not empty
}

//crething the node
struct Node* createNode(int value)                      // creates a new tree node
{
    struct Node *newNode;// pointer for new tree node

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;// stores value in node
    newNode->left = NULL; // initially no left child
    newNode->right = NULL; // initially no right child
    return newNode; // returns address of new node
}


//insert 
void insertNode(int value) 
{
    struct Node *current;// pointer for current tree node
    struct Node *newNode = createNode(value);// creates new tree node
    if (root == NULL) // checks if tree is empty
    {
        root = newNode;// new node becomes root
        printf("Node inserted successfully.\n");
        return; // stops the function
    }
    enqueue(root);// puts root into queue
    while (!isEmpty()) // runs while queue is not empty
    {
        current = dequeue(); // takes one tree node from queue
        if (current->left == NULL) // checks if left side is empty
        {
            current->left = newNode;// new node becomes left child
            printf("Node inserted successfully.\n");
            return;// complette insertionn
        }
        else
        {
            enqueue(current->left);  //puts left child into queue
        }
        if (current->right == NULL)// checks if right side is empty
        {
            current->right = newNode; //new node becomes right child
            printf("Node inserted successfully.\n");
            return; // insertion is completed
        }
        else
        {
            enqueue(current->right); // puts right child into queue
        }
    }
}
//  SEARCH USING QUEUE 
void searchNode(int value)
{
    struct Node *current;// pointer for current node
    if (root == NULL)// checks if tree is empty
    {
        printf("Tree is empty.\n");
        return; 
    }
    enqueue(root);// puts root into queue
    while (!isEmpty()) // runs while queue is not empty
    {
        current = dequeue();// gets one node from queue
        if (current->data == value)// checks current node's value
        {
            printf("Value found!\n");
            return;                                      
        }
        if (current->left != NULL)// checks if left child exists
        {
            enqueue(current->left);                      // puts left child into queue
        }
        if (current->right != NULL)                      // checks if right child exists
        {
            enqueue(current->right);                     // puts right child into queue
        }
    }
    printf("Value not found!\n");                        // value was not found
}
//  INORDER USING STACK 
void inorder()
{
    struct Node *stack[MAX]; // creates stack of node pointers
    int top = -1;// stack is initially empty
    struct Node *current = root;// current starts from root
    while (current != NULL || top != -1) // continues while node/stack exists
    {
        while (current != NULL)                         // moves towards left side
        {
            stack[++top] = current; // pushes current node into stack
            current = current->left; // moves to left child
        }
        current = stack[top--]; // removes node from stack
        printf("%d ", current->data);// prints current node
        current = current->right; // moves to right child
    }
}
//  PREORDER USING STACK 
void preorder()
{
    struct Node *stack[MAX]; // creates stack of node pointers
    int top = -1; // stack is initially empty
    struct Node *current;// pointer for current node
    if (root == NULL) // checks if tree is empty
        return; // stops if tree is empty
    stack[++top] = root; // pushes root into stack
    while (top != -1)                                   // runs while stack is not empty
    {
        current = stack[top--];    // pops node from stack
        printf("%d ", current->data);                   // prints root/current first
        if (current->right != NULL)                     // checks if right child exists
        {
            stack[++top] = current->right;              // pushes right child
        }
        if (current->left != NULL)                      // checks if left child exists
        {
            stack[++top] = current->left; // pushes left child
        }
    }
}
//  POSTORDER USING TWO STACKS 
void postorder()
{
    struct Node *stack1[MAX];  // first stack for processing
    struct Node *stack2[MAX];   // second stack for reversing order
    int top1 = -1;                                      // Stack 1 is initially empty
    int top2 = -1;                                      // Stack 2 is initially empty
    struct Node *current;// pointer for current node
    if (root == NULL)// checks if tree is empty
        return; // stops if tree is empty
    stack1[++top1] = root;                              // pushes root into Stack 1
    while (top1 != -1)                                  // runs while Stack 1 is not empty
    {
        current = stack1[top1--]; // pops node from Stack 1
        stack2[++top2] = current;  // pushes node into Stack 2
        if (current->left != NULL)                               // checks if left child exists
        {
            stack1[++top1] = current->left;// pushes left child into Stack 1
        }
        if (current->right != NULL)                     // checks if right child exists
        {
            stack1[++top1] = current->right;// pushes right child into Stack 1
        }
    }
    while (top2 != -1)                                  // runs while Stack 2 is not empty
    {
        current = stack2[top2--];// pops node from Stack 2
        printf("%d ", current->data);  // prints node
    }
}
//  BREADTH TRAVERSAL 
void breadthTraversal()
{
    struct Node *current; // pointer for current node
    if (root == NULL)// checks if tree is empty
        return;// stops if tree is empty

        front=NULL;
        rear=NULL;
    enqueue(root); // puts root into queue
    while (!isEmpty()) // runs while queue is not empty
    {
        current = dequeue(); // gets node from queue
        printf("%d ", current->data); // prints current node
        if (current->left != NULL) // checks if left child exists
        {
            enqueue(current->left);  // adds left child to queue
        }
        if (current->right != NULL) // checks if right child exists
        {
            enqueue(current->right);// adds right child to queue
        }
    }
}
//  DEPTH TRAVERSAL 
void depthTraversal()
{
    struct Node *stack[MAX];                            // creates stack of node pointers
    int top = -1; // stack is initially empty
    struct Node *current;                               // pointer for current node
    if (root == NULL)// checks if tree is empty
        return;                            // stops if tree is empty
    stack[++top] = root;                         // pushes root into stack
    while (top != -1)                        // runs while stack is not empty
    {
        current = stack[top--];// pops node from stack
        printf("%d ", current->data); // prints current node
        if (current->right != NULL)// checks if right child exists
        {
            stack[++top] = current->right;// pushes right child
        }
        if (current->left != NULL) // checks if left child exists
        {
            stack[++top] = current->left;   // pushes left child
        }
    }
}
//  UPDATE USING QUEUE 
void updateNode(int oldValue, int newValue)
{
    struct Node *current;// pointer for current node
    if (root == NULL)                                   // checks if tree is empty
    {
        printf("Tree is empty.\n");
        return; // stops the function
    }
    enqueue(root); // puts root into queue
    while (!isEmpty()) // runs while queue is not empty
    {
        current = dequeue();// gets one node from queue
        if (current->data == oldValue)                  // checks for old value
        {
            current->data = newValue;// changes old value to new value
            printf("Value updated successfully.\n");
            return;                     // update completed
        }
        if (current->left != NULL)         // checks if left child exists
        {
            enqueue(current->left);    // adds left child to queue
        }
        if (current->right != NULL)       // checks if right child exists
        {
            enqueue(current->right);    // adds right child to queue
        }
    }
    printf("Value not found!\n");    // old value was not found
}
//  DELETE USING QUEUE 
void deleteNode(int value)
{
    struct Node *current;
    struct Node *target = NULL;
    struct Node *deepest = NULL;
    struct Node *parent = NULL;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    enqueue(root);
    while (!isEmpty())
    {
        current = dequeue();
        if (current->data == value)
        {
            target = current;
        }
        if (current->left != NULL)
        {
            parent = current;
            deepest = current->left;
            enqueue(current->left);
        }
        if (current->right != NULL)
        {
            parent = current;
            deepest = current->right;
            enqueue(current->right);
        }
    }
    if (target == NULL)
    {
        printf("Value not found!\n");
        return;
    }
    // ==
    if (target->left == NULL && target->right == NULL)
    {
    if (parent->left == target) // parent   cha left ha apala target asel tr tyala null karaane 
        parent->left = NULL;
    else
    parent->right = NULL; //parenttt cha right  ha apala target asel tr tyala null karaaichh
    free(target);
    printf("Node deleted successfully.\n");
    return;
}
// ==
    if (deepest == NULL) // hee root sathiii
    {
        free(root);
        root = NULL;
        printf("Node deleted successfully.\n");
        return;
    }
    target->data = deepest->data;
    if (parent->right == deepest) // he check karat kki deepest he parent chya right la ahe ka ahee tr delete 
    {
        parent->right = NULL;
    }
    else
    {
        parent->left = NULL; // // he check karat kki deepest he parent chya left la ahe ka ahee tr delete 
    }
    free(deepest);
    printf("Node deleted successfully.\n");
}
int main()
{
    int choice;              // stores menu choice
    int value;             // stores value
    int oldValue;  // stores old value
    int newValue;        // stores new value
    while (1)// keeps menu running
    {
        printf("\n\n========== BINARY TREE MENU ==========\n");
        printf("1. Create / Insert\n");                 
        printf("2. Read / Display\n");               
        printf("3. Update\n");                          
        printf("4. Delete\n");                       
        printf("5. Exit\n");                        
        printf("6. Search Using Queue\n");              
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);                           // takes menu choice
        switch (choice)                                 // checks selected option
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);                    // takes value to insert
                insertNode(value);                     // calls insert function
                break;                                 // exits this case
            case 2:
                if (root == NULL)                       // checks if tree is empty
                {
                    printf("Binary tree is empty.\n");
                }
                else
                {
                    printf("\nInorder: ");
                    inorder();  // calls inorder traversal
                    printf("\nPreorder: ");
                    preorder();                                                            // calls preorder traversal
                    printf("\nPostorder: ");
                    postorder();                                                                     // calls postorder traversal
                    printf("\nBreadth Traversal: ");
                    breadthTraversal();                // calls breadth traversal
                    printf("\nDepth Traversal: ");
                    depthTraversal();    // calls depth traversal
                    printf("\n");
                }
                break;                                  // exits this case
            case 3:
                printf("Enter old value: ");
                scanf("%d", &oldValue);                  // takes old value
                printf("Enter new value: ");
                scanf("%d", &newValue);                 // takes new value
                updateNode(oldValue, newValue);         // calls update function
                break;                                  // exits this case
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &value);                    // takes value to delete
                deleteNode(value);                      // calls delete function
                break;                                  // exits this case
            case 5:
                printf("Exiting program...\n");
                exit(0);                                // completely stops program
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);                    // takes value to search
                searchNode(value);                      // calls search function
                break;                                  // exits this case
            default:
                printf("Invalid choice!\n");            // runs for invalid choice
        }
    }
    return 0;                                           
}