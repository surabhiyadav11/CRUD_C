#include <stdio.h>
#include <stdlib.h> //malloc(),free()
#include <string.h>

struct StudentInfo
{
    unsigned int rollno; // non-negative integer values only if given does not throw error it converts negative value in unsigned int
    char name[50];       // maximum 49 characters can be stored because one character is reserved for '\0'.
    struct StudentInfo *left;
    struct StudentInfo *right;
};

struct StudentInfo *root = NULL; // a pointer named root that can store the address of a StudentInfo node


// Queue used for breadths first traversal and insertion
struct Queue                         // defines structure only
{
    struct StudentInfo *data;        // points to the actual StudentInfo node
    struct Queue *next;              // points to the next queue node
};

struct Queue *front = NULL;          // points to the first queue node
struct Queue *rear = NULL;           // points to the last queue node


// Stack for iterative traversals
struct Stack                         // defines structure only
{
    struct StudentInfo *data;        // points to the actual StudentInfo node
    struct Stack *next;              // points to the next stack node
};

struct Stack *top = NULL;             // points to the top stack node



// validation part

void clearInput()
{
    while (getchar() != '\n')
        ; // removes the remaining characters from the input buffer until the newline character is found
}

int queueempty()
{
    return front == NULL; // returns 1 if queue is empty and 0 if queue is not empty
}



int validName(char *name)
{
    int i;

    if (name[0] == '\0') // first character is \0 or not .'\0' tells C that the string ends here
        return 0;

    for (i = 0; name[i] != '\0'; i++) // stops when '\0' is reached
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||(name[i] >= 'a' && name[i] <= 'z') ||name[i] == ' ')) // checks that name[i] contains only uppercase lowercase or a space if it contains anything else, ! makes the condition true and return 0 marks the name as invalid
        {
            return 0;
        }
    }

    return 1; // valid
}



// Adds a node pointer into the queue
void enqueue(struct StudentInfo *node)
{
    struct Queue *newNode;

    newNode = (struct Queue *)malloc(sizeof(struct Queue));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = node; // stores the address of the actual StudentInfo node
    newNode->next = NULL; // new queue node is initially the last node

    if (rear == NULL) // if queue is empty
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode; // connects new node after the last node
        rear = newNode;       // new node becomes the rear
    }
}



// Removes a node from the queue
struct Queue *dequeue()
{
    struct Queue *temp;

    if (queueempty())
        return NULL;

    temp = front;            // gets the first queue node
    front = front->next;     // moves front to the next queue node

    if (front == NULL)       // if queue becomes empty
        rear = NULL;

    temp->next = NULL;       // separates removed node from queue
    return temp;             // returns the removed node
}



// Inserts nodes level by level using a queue (BFS)
void addNode(unsigned int rollno, char *name)
{
    struct StudentInfo *node; // pointer for the new node
    struct Queue *temp;       // pointer for a temporary queue node used during traversal
    struct StudentInfo *current; // pointer to the actual StudentInfo node

    node = (struct StudentInfo *)malloc(sizeof(struct StudentInfo)); // memory allocation to new node

    if (node == NULL) // checking allocation
    {
        printf("Memory allocation failed\n");
        return;
    }

    node->rollno = rollno; // stores values in new node
    strcpy(node->name, name);
    node->left = NULL;  // initially new node, no child
    node->right = NULL;

    if (root == NULL) // if tree empty new node becomes root node
    {
        root = node;
        return;
    }

    front = NULL; // resetting queue before traversal
    rear = NULL;

    enqueue(root);

    while (!queueempty())
    {
        temp = dequeue();

        current = temp->data; // gets the actual StudentInfo node directly

        if (current->left == NULL)
        {
            current->left = node;
            free(temp);
            return;
        }
        else
            enqueue(current->left); // the left child is added to the queue to check later

        if (current->right == NULL)
        {
            current->right = node;
            free(temp);
            return;
        }
        else
            enqueue(current->right);

        free(temp);
    }
}



// Level order display
void display()
{
    struct Queue *node; // a pointer to store the queue node removed from the queue
    struct StudentInfo *current;

    if (root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }

    front = NULL; // reset queue
    rear = NULL;

    enqueue(root);

    while (!queueempty())
    {
        node = dequeue();

        current = node->data; // gets the actual StudentInfo node

        printf("Roll No: %u  Name: %s\n",
               current->rollno, current->name); // %u unsigned int

        if (current->left != NULL)
            enqueue(current->left);

        if (current->right != NULL)
            enqueue(current->right);

        free(node);
    }
}



// Recursive traversals

void inorder(struct StudentInfo *node) // L-N-R
{
    if (node != NULL)
    {
        inorder(node->left);

        printf("Roll No: %u, Name: %s\n",
               node->rollno, node->name);

        inorder(node->right);
    }
}



void preorder(struct StudentInfo *node) // N-L-R
{
    if (node != NULL)
    {
        printf("Roll No: %u, Name: %s\n",
               node->rollno, node->name);

        preorder(node->left);
        preorder(node->right);
    }
}



void postorder(struct StudentInfo *node) // L-R-N
{
    if (node != NULL)
    {
        postorder(node->left);
        postorder(node->right);

        printf("Roll No: %u, Name: %s\n",
               node->rollno, node->name);
    }
}



// Push operation for iterative traversals
void push(struct StudentInfo *node)
{
    struct Stack *newNode;

    newNode = (struct Stack *)malloc(sizeof(struct Stack)); // creates a new stack node dynamically

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = node; // stores the address of the actual StudentInfo node
    newNode->next = top;  // new stack node points to the previous top node
    top = newNode;        // new node becomes the new top
}



// Pop operation for iterative traversals
struct Stack *pop()
{
    struct Stack *temp;

    if (top == NULL) // the stack is empty
        return NULL;

    temp = top;      // gets the top stack node
    top = top->next; // moves top to the next stack node

    temp->next = NULL; // separates removed node from stack
    return temp;        // returns the removed stack node
}



// Iterative inorder traversal
void inorderIterative() // L-N-R
{
    struct StudentInfo *node = root;
    struct Stack *temp;

    top = NULL; // reset stack before traversal

    while (node != NULL || top != NULL)
    {
        while (node != NULL)
        {
            push(node);       // pushes current node into linked-list stack
            node = node->left; // moves to left child
        }

        temp = pop(); // gets the top node from linked-list stack

        printf("Roll No: %u, Name: %s\n",
               temp->data->rollno, temp->data->name);

        node = temp->data->right; // directly gets right child

        free(temp); // releases memory of the removed stack node
    }
}



// Iterative preorder traversal
void preorderIterative() // N-L-R
{
    struct Stack *temp;
    struct StudentInfo *node;

    if (root == NULL)
        return;

    top = NULL; // reset stack before traversal

    push(root); // push root first

    while (top != NULL)
    {
        temp = pop(); // gets top node from linked-list stack

        node = temp->data; // gets the actual StudentInfo node

        printf("Roll No: %u, Name: %s\n",
               node->rollno, node->name);

        if (node->right != NULL)
            push(node->right); // push right first

        if (node->left != NULL)
            push(node->left); // push left after right

        free(temp); // releases memory of the removed stack node
    }
} // Why right first, coz stack follows LIFO so left must come out first



// Iterative postorder traversal
void postorderIterative() // L-R-N
{
    struct Stack *temp;
    struct Stack *top2 = NULL; // top pointer for the second linked-list stack
    struct Stack *temp2;
    struct StudentInfo *node;

    if (root == NULL)
        return;

    top = NULL; // reset main stack

    push(root);

    while (top != NULL)
    {
        temp = pop(); // gets node from main stack

        node = temp->data; // gets the actual StudentInfo node

        // create another linked-list stack node for the second stack
        temp2 = (struct Stack *)malloc(sizeof(struct Stack));

        if (temp2 == NULL)
        {
            printf("Memory allocation failed\n");
            free(temp);
            return;
        }

        temp2->data = node; // stores pointer to the actual StudentInfo node
        temp2->next = top2; // new node points to previous top of second stack
        top2 = temp2;       // new node becomes the top of second stack

        if (node->left != NULL)
            push(node->left); // push left child

        if (node->right != NULL)
            push(node->right); // push right child

        free(temp); // releases memory of the first stack node
    }

    while (top2 != NULL)
    {
        temp2 = top2;       // gets the top node of second stack
        top2 = top2->next;  // moves top2 to the next stack node

        printf("Roll No: %u, Name: %s\n",
               temp2->data->rollno, temp2->data->name);

        free(temp2); // releases memory of the second stack node
    }
}



// Update
void update(unsigned int rollno, char *name)
{
    struct Queue *node; // pointer to store the address of the queue node removed from the queue
    struct StudentInfo *current;

    if (root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }

    front = NULL; // reset queue before starting traversal
    rear = NULL;

    enqueue(root); // start searching from root

    while (!queueempty())
    {
        node = dequeue(); // gets the next queue node from the queue

        current = node->data; // gets the actual StudentInfo node

        if (current->rollno == rollno) // checks whether roll number matches
        {
            strcpy(current->name, name); // replaces old name with new name

            printf("Name updated successfully\n");

            free(node);

            return; // update is completed, so function ends
        }

        if (current->left != NULL)
            enqueue(current->left); // add left child to check later

        if (current->right != NULL)
            enqueue(current->right); // add right child to check later

        free(node);
    }

    printf("Roll number not found\n"); // roll number was not present in tree
}



// Deletes a node by replacing it with the last level-order node
void deleteNode(unsigned int rollno)
{
    struct StudentInfo *child;      // pointer used to search for the required node
    struct StudentInfo *parent;     // stores current node during second traversal
    struct StudentInfo *last;       // stores the last node in level-order
    struct StudentInfo *lastParent; // stores the parent of the last node
    struct StudentInfo *found;      // stores the node that should be deleted
    struct Queue *qnode;

    if (root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }

    front = NULL; // reset queue before searching
    rear = NULL;

    enqueue(root); // start level-order traversal from root

    found = NULL; // initially assume the required node is not found

    while (!queueempty())
    {
        qnode = dequeue(); // gets the next queue node

        child = qnode->data; // gets the actual StudentInfo node

        if (child->rollno == rollno) // checks whether roll number matches
        {
            found = child; // store the address of the node to be deleted

            free(qnode);

            break; // node is found, so stop searching
        }

        if (child->left != NULL)
            enqueue(child->left); // add left child to check later

        if (child->right != NULL)
            enqueue(child->right); // add right child to check later

        free(qnode);
    }

    if (found == NULL) // if required node was not found
    {
        printf("Roll number not found\n");
        return;
    }


    // special case - tree contains only one node
    if (found == root && root->left == NULL && root->right == NULL)
    {
        root = NULL; // tree becomes empty

        free(found); // release memory of the deleted node

        printf("Node deleted successfully\n");

        return;
    }


    // finding the last node in level-order
    front = NULL; // reset the queue
    rear = NULL;

    enqueue(root); // start level-order traversal again from root

    last = root;       // initially assume root is the last node
    lastParent = NULL; // parent of last node is not known yet

    while (!queueempty())
    {
        qnode = dequeue(); // gets the next queue node

        parent = qnode->data; // gets the actual StudentInfo node

        last = parent; // this node becomes the current last node

        if (parent->left != NULL) // check whether left child exists
        {
            lastParent = parent;   // store its parent
            enqueue(parent->left); // add left child to the queue
        }

        if (parent->right != NULL) // check whether right child exists
        {
            lastParent = parent;    // store its parent
            enqueue(parent->right); // add right child to the queue
        }

        free(qnode);
    }


    // copy the last node's data into the node to be deleted
    found->rollno = last->rollno;
    strcpy(found->name, last->name);


    // remove the last node from its parent's link
    if (lastParent->right == last) // checks whether last is the right child
        lastParent->right = NULL;
    else
        lastParent->left = NULL; // otherwise last is the left child

    free(last); // release memory of the last node

    printf("Node deleted successfully\n");
}



int main()
{
    int n, choice, i;
    unsigned int rollno;
    char name[50];
    int attempts;
    char extra; // stores an extra character entered by the user to detect input such as 12abc or 12 3

    for (attempts = 1; attempts <= 3; attempts++)
    {
        printf("Enter number of students: ");

        if (scanf("%d%c", &n, &extra) == 2 &&
            extra == '\n' &&
            n > 0 &&
            n <= 10)
            break;

        // if %c already reads '\n', clearInput() is not needed.
        // calling it again may make the program wait for another Enter.

        if (extra != '\n') // if it is a space or any other character, extra input is still present
            clearInput();  // so clearInput() is needed to remove the remaining input from the buffer

        printf("Invalid input! Enter number of students between 1 to 10.\n");
    }

    if (attempts > 3)
    {
        printf("3 attempts completed. Program ended.\n");
        return 0;
    }


    for (i = 0; i < n; i++)
    {
        printf("\nEnter details of student %d\n", i + 1);

        for (attempts = 1; attempts <= 3; attempts++)
        {
            printf("Enter roll number: ");

            if (scanf("%u%c", &rollno, &extra) == 2 &&
                extra == '\n' &&
                rollno > 0)
                break;

            if (extra != '\n')
                clearInput();

            printf("Invalid roll number! Enter a integer value.\n");
        }

        if (attempts > 3)
        {
            printf("3 attempts completed. Student not inserted.\n");
            continue;
        }


        for (attempts = 1; attempts <= 3; attempts++)
        {
            printf("Enter name: ");

            if (scanf(" %49[^\n]", name) == 1) // %49[^\n] reads up to 49 characters until Enter (\n) is found.
                                               // it allows spaces inside the name
            {
                extra = getchar();

                if (extra == '\n' && validName(name))
                    break; // If the name is valid, stop the name-input loop
            }

            clearInput();

            printf("Invalid name! Please enter a valid name.\n");
        }

        if (attempts > 3)
        {
            printf("3 attempts completed. Student not inserted.\n");
            continue;
        }

        addNode(rollno, name);

        printf("Student inserted successfully\n");
    }



    while (1)
    {
        printf("\n1. Insert\n");
        printf("2. Recursive Display\n");
        printf("3. Iterative Display\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Exit\n");


        for (attempts = 1; attempts <= 3; attempts++)
        {
            printf("Enter your choice: ");

            if (scanf("%d%c", &choice, &extra) == 2 && extra == '\n' &&choice >= 1 &&choice <= 6)
                break;

            if (extra != '\n')
                clearInput();

            printf("Invalid choice! Please enter a number from 1 to 6\n");
        }

        if (attempts > 3)
        {
            printf("3 attempts completed. Program ended.\n");
            break;
        }


        switch (choice)
        {
        case 1:

            for (attempts = 1; attempts <= 3; attempts++)
            {
                printf("Enter roll number: ");

                if (scanf("%u%c", &rollno, &extra) == 2 &&extra == '\n' &&rollno > 0)
                    break;

                clearInput();

                printf("Invalid roll number! \n");
            }

            if (attempts > 3)
            {
                printf("3 attempts completed. Insert cancelled.\n");
                break;
            }


            for (attempts = 1; attempts <= 3; attempts++)
            {
                printf("Enter name: ");

                if (scanf(" %49[^\n]", name) == 1)
                {
                    extra = getchar();

                    if (extra == '\n' && validName(name))
                        break;
                }

                clearInput();

                printf("Invalid name! Attempt %d of 3\n", attempts);
            }

            if (attempts > 3)
            {
                printf("3 attempts completed. Insert cancelled.\n");
                break;
            }

            addNode(rollno, name);

            printf("Student inserted successfully\n");

            break;


        case 2:

            if (root == NULL)
            {
                printf("Tree is empty\n");
                break;
            }

            printf("\n--- LEVEL ORDER (QUEUE) ---\n");
            display();

            printf("\n--- INORDER (RECURSIVE) ---\n");
            inorder(root);

            printf("\n--- PREORDER (RECURSIVE) ---\n");
            preorder(root);

            printf("\n--- POSTORDER (RECURSIVE) ---\n");
            postorder(root);

            break;


        case 3:

            if (root == NULL)
            {
                printf("Tree is empty\n");
                break;
            }

            printf("\n--- LEVEL ORDER (QUEUE) ---\n");
            display();

            printf("\n--- INORDER (ITERATIVE) ---\n");
            inorderIterative();

            printf("\n--- PREORDER (ITERATIVE) ---\n");
            preorderIterative();

            printf("\n--- POSTORDER (ITERATIVE) ---\n");
            postorderIterative();

            break;


        case 4:

            if (root == NULL)
            {
                printf("Tree is empty\n");
                break;
            }

            for (attempts = 1; attempts <= 3; attempts++)
            {
                printf("Enter roll number to update: ");

                if (scanf("%u%c", &rollno, &extra) == 2 &&
                    extra == '\n' &&
                    rollno > 0)
                    break;

                clearInput();

                printf("Invalid roll number! \n");
            }

            if (attempts > 3)
            {
                printf("3 attempts completed. Update cancelled.\n");
                break;
            }


            for (attempts = 1; attempts <= 3; attempts++)
            {
                printf("Enter new name: ");

                if (scanf(" %49[^\n]", name) == 1)
                {
                    extra = getchar();

                    if (extra == '\n' && validName(name))
                        break;
                }

                clearInput();

                printf("Invalid name! Attempt %d of 3\n", attempts);
            }

            if (attempts > 3)
            {
                printf("3 attempts completed. Update cancelled.\n");
                break;
            }

            update(rollno, name);

            break;


        case 5:

            if (root == NULL)
            {
                printf("Tree is empty\n");
                break;
            }

            for (attempts = 1; attempts <= 3; attempts++)
            {
                printf("Enter roll number to delete: ");

                if (scanf("%u%c", &rollno, &extra) == 2 &&
                    extra == '\n' &&
                    rollno > 0)
                    break;

                clearInput();

                printf("Invalid roll number! Attempt %d of 3\n", attempts);
            }

            if (attempts > 3)
            {
                printf("3 attempts completed. Delete cancelled.\n");
                break;
            }

            deleteNode(rollno);

            break;


        case 6:

            printf("Program ended.\n");
            return 0;
        }
    }

    return 0;
}