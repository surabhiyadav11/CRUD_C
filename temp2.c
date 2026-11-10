#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentInfo {
    unsigned int rollno;      //no negative values
    char name[50];
    struct StudentInfo *left;
    struct StudentInfo *right;
    int isThread;
};
// isThread=0 -> right is a real right child or null
// isThread=1 -> right is a thread to an actual inorder successor

struct StudentInfo *root = NULL;

struct QueueNode{
    struct StudentInfo *data;;              
    struct QueueNode *next;
};
struct QueueNode *queueFront = NULL;
struct QueueNode *queueRear = NULL;

struct StackNode{
    struct StudentInfo *data;
    struct StackNode *next;
};
struct StackNode *stackTop=NULL;

void clearInput() {
    while (getchar() != '\n');//scanf cannot consume abc so it remain in the input buffer and keeps reading till newline
}

int queue_empty() {
    return queueFront == NULL;
}
int validName(char name[]) {
    int i;
    if (name[0] == '\0') {     //checks whether the first character is the string terminator(\0)-it marks the end of the string
        return 0;
    }
    for (i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == ' ')) {
            return 0;
        }
    }
    return 1;
}
void copyName(char destination[], char source[]) {
    int i = 0;

    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }

    destination[i] = '\0';
}

void enqueue(struct StudentInfo *data)
{
    struct QueueNode *newNode;

    newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));

    if (newNode == NULL) {
        printf("Queue overflow! Memory allocation failed.\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (queueRear == NULL) {

        // Queue is empty
        queueFront = newNode;
        queueRear = newNode;
    }
    else {

        // Add at rear
        queueRear->next = newNode;
        queueRear = newNode;
    }
}                     

struct StudentInfo *dequeue() 
{
    struct QueueNode *temp;
    struct StudentInfo *data;

    if (queueFront == NULL) {
        return NULL;
    }

    temp = queueFront;

    data = temp->data;

    queueFront = queueFront->next;

    if (queueFront == NULL) {
        queueRear = NULL;
    }

    free(temp);

    return data;
}
void push(struct StudentInfo *data)
{
    struct StackNode *newNode;

    newNode = (struct StackNode *)malloc(sizeof(struct StackNode));

    if (newNode == NULL) {
        printf("Stack overflow! Memory allocation failed.\n");
        return;
    }

    newNode->data = data;
    newNode->next = stackTop;
    stackTop = newNode;
}

struct StudentInfo *pop()
{
    struct StackNode *temp;
    struct StudentInfo *data;
    if (stackTop == NULL) {
        return NULL;
    }

    temp = stackTop;
    data = temp->data;

    stackTop = stackTop->next;

    free(temp);

    return data;
}

struct StudentInfo *peek(){
    if (stackTop == NULL) {
        return NULL;
    }

    return stackTop->data;
}

int stackEmpty()
{
    return stackTop == NULL;
}

void addNode(unsigned int rollno, char name[]) {
    struct StudentInfo *node;  //it represents new student
    struct StudentInfo *temp;  //used for traversing tree

    node = (struct StudentInfo *)malloc(sizeof(struct StudentInfo));

    node->rollno = rollno;
    copyName(node->name, name);//copy the entered name into the node
    
    node->left = NULL;
    node->right = NULL;
    node->isThread =0;                                                                                                     //right pointer initially considered a real right child pointer which points to null
  
    if(root == NULL) {  //checks whether the tree is empty
        root = node;     // if tree is empty , the new node becomes the root
        return;
    }

    temp=root;
    while(1){
        if(rollno<temp->rollno){
            if(temp->left==NULL){
                
                node->right = temp;          //thread to inorder successor
                node->isThread=1;
                
                temp->left=node;
                return;
            }
            else{
                temp=temp->left;
            }
        }
        else if(rollno>temp->rollno){
                  if(temp->isThread ==1 || temp->right == NULL){   //right is a null or right is a thread
                  
                                                  
                    node->right = temp->right; 
                    
                    //it is just used for copies old right pointer
                    //            50
                    //           /
                    //          30------->50
                    //after inserting 40--->  40.right=30.right
                    
                    node->isThread=temp->isThread;

                    temp->right = node;
                    temp->isThread = 0;

                    return;
                  }
            else{
                temp=temp->right;
            }
        }
        else{
            printf("Roll No aiready exits\n");
            free(node);
            return;
        }
    }    
}

void display() {
    struct StudentInfo *node;       //temporary pointer used for traversing

    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }


    enqueue(root);     //starts trversing from root

    while (!queue_empty()) {
        node = dequeue();           //take next student

        printf("Roll No: %u  Name: %s\n", node->rollno, node->name);
        if (node->left != NULL) {         //if left child is exists,add it to the queue
            enqueue(node->left);
        }
        if (node->right != NULL && node->isThread == 0) {        //if right child is exists,add it to the queue
            enqueue(node->right);
        }
    }
}
void inorder(struct StudentInfo *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("Roll No: %d, Name: %s\n", root->rollno, root->name);
        if(root->isThread == 0){             //only go right recursively if right is a real child
            inorder(root->right);
        }
    }
}

void preorder(struct StudentInfo *root)
{
    if (root != NULL)
    {
        printf("Roll No: %d, Name: %s\n", root->rollno, root->name);
        preorder(root->left);
        if(root->isThread == 0){
            preorder(root->right);        //only go right recursively if right is a real child
        }
    }
}

void postorder(struct StudentInfo *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        if(root->isThread == 0){
            postorder(root->right);          //only go right recursively if right is a real child
        }
        printf("Roll No: %d, Name: %s\n", root->rollno, root->name);
    }
}

// right-threaded bst is especially useful because inorder traversal can be done without a stack
void inorderIterative(){
    
    struct StudentInfo *node;

    if(root==NULL){
        return;
    }
    node=root;

    //find the leftmost child
    while(node->left != NULL){
        node=node->left;
    }

    while(node != NULL){
        printf("Roll no : %u , Name : %s \n",node->rollno,node->name);

        if(node->isThread == 1){
            //right points directly to inorder successor
            node=node->right;
        }
        else{
            //go to the right subtree,then find its leftmost node
            node=node->right;

            while(node!=NULL  && node->left != NULL){
                node=node->left;
            }
        }
    }
}
void preorderIterative()
{
    stackTop = NULL;

    struct StudentInfo *node;

    if (root == NULL)
        return;

    push(root);      

    while (!stackEmpty())
    {
        node=pop();     //pop now returns void* so used typecast

        printf("Roll No: %u, Name: %s\n", node->rollno, node->name);
        //pushes right first and then left. why-bcoz stack follows LIFO
        if (node->right != NULL && node->isThread == 0)
            push(node->right);

        if (node->left != NULL)
            push(node->left);
    }
}
void postorderIterative()
{
    if (root == NULL)
        return;

    stackTop = NULL;   //reset the stack before starting traversal

    struct StudentInfo *node = root;
    struct StudentInfo *previous = NULL;   //stores the previously processed node

    while (node != NULL || !stackEmpty())
    {
        if (node != NULL)         //moves to the most left node
        {
            push(node);          //push the current node into the stack
            node = node->left;   //move to the left child
        }
        else                     //if node==NULL
        {
            node =peek();       //look at the top node without removing it

            //if real right child exists then move to the right child
            if (node->right != NULL && node->isThread == 0 && previous != node->right)    //only follow right if it is a real child
            {
                node = node->right;   //move to the right child
            }
            else
            {
                //both left and right subtrees are processed
                printf("Roll No: %u, Name: %s\n",node->rollno, node->name);
                       
                previous = pop();   //remove the node from stack
                node = NULL;        //indicate that current node is processed
            }
        }
    }
}

//function to find a student by roll number and change their name
void update(unsigned int rollno, char name[]) {
    struct StudentInfo *node;

    node=root;

    while(node!=NULL){
        if(rollno==node->rollno){
            copyName(node->name,name);
            printf("Name updated successfully\n");
            return;
        }
        else if(rollno<node->rollno){
            node=node->left;
        }
        else{
            if(node->isThread == 1){
                break;
            }
            node=node->right;
        }
    }
    printf("Roll no not found\n");
}

void deleteNode(unsigned int rollno) {
    struct StudentInfo *parent;                //parent of current
    struct StudentInfo *current;               //this points to the node we r currently looking at
    struct StudentInfo *successor;             //this is used only when the node we want to delete has two children
    struct StudentInfo *successorParent;       //parent of successor    
    struct StudentInfo *temp;

    current=root;
    parent=NULL;

    while(current!=NULL && current->rollno!=rollno){   //keep searching up to end till we found roll no
        parent=current;

        if(rollno<current->rollno){
            current=current->left;
        }
        else{
            // if right is a thread , there is no right subtree
            if(current->isThread == 1){
                current = NULL;
            }
            else{
                current=current->right;
            }
        }
    }
    if(current==NULL){
        printf("Roll No not found\n");
        return;
    }

    if(current-> left!=NULL && current->right !=NULL && current->isThread == 0){     //node have both real child
        successorParent=current;
        successor=current->right;

        while(successor->left !=NULL){
            successorParent=successor;
            successor=successor->left;
        }
        
        //copy successor data into current data
        current->rollno = successor->rollno;
        copyName(current->name,successor->name);
        
        //now delete the successor instead
        current=successor;
        parent=successorParent;
    }

    if(current->left == NULL && (current->right == NULL || current->isThread == 1)){   //current has no left child no real right child
        if(parent == NULL){                   //special case-deleting root
            root = NULL;
        }
        else if(parent->left == current){
            parent->left = NULL;
        }
        else{
            //current was parents right child,so parents right should now become a thread

            parent->right=current->right;
            parent->isThread = 1;
        }
    }

    else if(current->left != NULL && (current->right == NULL || current->isThread == 1)){             //current has only a left child
        
        //find rightmost node in left subtree
        //its thread currently points to current
        //after deletion it must point to current's successor
        //before deleting a node,we have to update the predecessors thread
        temp=current->left;
        while(temp->isThread == 0 && temp->right != NULL){
            temp=temp->right;
        }
        temp->right=current->right;
        temp->isThread =1;

        //connect parent to currents left child
        if(parent == NULL){                //if current is root,means node being deleted is the root
            root=current->left;
        }
        else if(parent->left == current){    //if current is the left child of parent
            parent->left = current->left;    //this is after deleting internode between parent and current->left that is parent->left
        }
        else{                               //if current is the right child of parent
            parent->right = current->left;  //this is after deleting internode between parent and current-left that is parent->right
            parent->isThread = 0;
        }
    }

    else{                                   //current has only a right child
        if(parent==NULL){                   //if there is no parent
            root=current->right;            //the right child becomes the new root
        }
        else if(parent->left == current){   //if current is left child of parent
            parent->left=current->right;    //this is after deleting internode between parent and current->right that is parent->left
        }
        else{                               //if current is right child of parent
            parent->right = current->right; //this is after deleting internode between parent and current->right that is parent->right
            parent->isThread = 0;
        }
    }
    free(current);
    printf("Node deleted successfully\n");

}

int main() {
    int n, choice, i;    //n-number of initial students
    unsigned int rollno;
    char name[50];
    int attempts;
    char extra;          //used to detect unwanted input

    for (attempts = 1; attempts <= 3; attempts++) {
        printf("Enter number of students: ");

        if (scanf("%d%c", &n, &extra) == 2 &&
            extra == '\n' && n > 0 && n <= 10) {    //here the extra character is newline
            break;              //input is valid,so leave the attempts loop
        }
        clearInput();
        printf("Invalid input! Attempt %d of 3\n", attempts);
    }
    if (attempts > 3) {
        printf("3 attempts completed. Program ended.\n");
        return 0;
    }
    for (i = 0; i < n; i++) {
        printf("\nEnter details of student %d\n", i + 1);
        for (attempts = 1; attempts <= 3; attempts++) {
            printf("Enter roll number: ");
            if (scanf("%u%c", &rollno, &extra) == 2 &&
                extra == '\n' && rollno > 0) {
                break;
            }
            clearInput();
            printf("Invalid roll number! Attempt %d of 3\n", attempts);
        }

        if (attempts > 3) {
            printf("3 attempts completed. Student not inserted.\n");
            continue;
        }
        for (attempts = 1; attempts <= 3; attempts++) {
            printf("Enter name: ");
            if (scanf(" %49[^\n]", name) == 1) {//reads the student name up to 49 characters,including spaces,untill the user presses enter
                extra = getchar();              //reads the next character after the name,usually newline
                if (extra == '\n' && validName(name)) {
                    break;
                }
            }
            clearInput();
            printf("Invalid name! Attempt %d of 3\n", attempts);
        }
        if (attempts > 3) {
            printf("3 attempts completed. Student not inserted.\n");
            continue;
        }
        addNode(rollno, name);
        printf("Student inserted successfully\n");
    }

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Recursive Display\n");
        printf("3. Iterative Display\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Exit\n");
        for (attempts = 1; attempts <= 3; attempts++) {
            printf("Enter your choice: ");
            if (scanf("%d%c", &choice, &extra) == 2 &&
                extra == '\n' && choice >= 1 && choice <= 6) {
                break;
            }
            clearInput();
            printf("Invalid choice! Attempt %d of 3\n", attempts);
        }
        if (attempts > 3) {
            printf("3 attempts completed. Program ended.\n");
            break;
        }
        switch (choice) {
            case 1:
                for (attempts = 1; attempts <= 3; attempts++) {
                    printf("Enter roll number: ");
                    if (scanf("%u%c", &rollno, &extra) == 2 &&
                        extra == '\n' && rollno > 0) {
                        break;
                    }
                    clearInput();
                    printf("Invalid roll number! Attempt %d of 3\n",
                           attempts);
                }
                if (attempts > 3) {
                    printf("3 attempts completed. Insert cancelled.\n");
                    break;
                }
                for (attempts = 1; attempts <= 3; attempts++) {
                    printf("Enter name: ");
                    if (scanf(" %49[^\n]", name) == 1) {
                        extra = getchar();
                        if (extra == '\n' && validName(name)) {
                            break;
                        }
                    }
                    clearInput();
                    printf("Invalid name! Attempt %d of 3\n", attempts);
                }
                if (attempts > 3) {
                    printf("3 attempts completed. Insert cancelled.\n");
                    break;
                }
                addNode(rollno, name);
                printf("Student inserted successfully\n");
                break;
            case 2:
                printf("\n--- RECURSIVE LEVEL ORDER ---\n");
                display();

                printf("\n--- RECURSIVE INORDER ---\n");
                inorder(root);

                printf("\n--- RECURSIVE PREORDER ---\n");
                preorder(root);

                printf("\n--- RECURSIVE POSTORDER ---\n");
                postorder(root);

                break;

            case 3:
                printf("\n--- ITERATIVE LEVEL ORDER ---\n");
                display();

                printf("\n--- ITERATIVE INORDER ---\n");
                inorderIterative();

                printf("\n--- ITERATIVE PREORDER ---\n");
                preorderIterative();

                printf("\n--- ITERATIVE POSTORDER ---\n");
                postorderIterative();

                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty\n");
                    break;
                }
                for (attempts = 1; attempts <= 3; attempts++) {
                    printf("Enter roll number to update: ");
                    if (scanf("%u%c", &rollno, &extra) == 2 &&
                        extra == '\n' && rollno > 0) {
                        break;
                    }
                    clearInput();
                    printf("Invalid roll number! Attempt %d of 3\n",
                           attempts);
                }
                if (attempts > 3) {
                    printf("3 attempts completed. Update cancelled.\n");
                    break;
                }
                for (attempts = 1; attempts <= 3; attempts++) {
                      printf("Enter new name: ");

                      if (scanf(" %49[^\n]", name) == 1) {
                            extra = getchar();

                      if (extra == '\n' && validName(name)) {
                      break;
                    }
                }

                    clearInput();
                    printf("Invalid name! Attempt %d of 3\n", attempts);
                }

                if (attempts > 3) {
                         printf("3 attempts completed. Update cancelled.\n");
                         break;
                }
                update(rollno,name);
                break;
            case 5:
                if (root == NULL) {
                    printf("Tree is empty\n");
                    break;
                }
                for (attempts = 1; attempts <= 3; attempts++) {
                    printf("Enter roll number to delete: ");
                    if (scanf("%u%c", &rollno, &extra) == 2 &&
                        extra == '\n' && rollno > 0) {
                        break;
                    }
                    clearInput();
                    printf("Invalid roll number! Attempt %d of 3\n",
                           attempts);
                }
                if (attempts > 3) {
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