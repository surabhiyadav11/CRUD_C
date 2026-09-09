#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next; 
};

struct Node *front = NULL;
struct Node *rear = NULL;

// =================================================
int isEmpty() {
    return front == NULL;
}
// =================================================
void enqueue(int value) {
  
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;  
    newNode->next = NULL;


    if (front == NULL) 
    {
        front = rear = newNode;
    } 
    else 
    {
        
        rear->next = newNode;
        rear = newNode;    
    }

    printf("%d inserted in the queue\n", value);
}


// =================================================
void dequeue() {

    if (isEmpty())
    {
        printf("Queue is EMPTY!\n");
    }
    else
    {
        struct Node *ptr = front;
        printf("%d removed from the queue\n", front->data);

       
        front = front->next;
        
        if (front == NULL) 
        {
            rear = NULL;
        }

        free(ptr);
    }
}
// =================================================

void display() {

    if (isEmpty()) 
    {
       printf("Queue is EMPTY!\n");
    } 
    else 
    {
        struct Node *temp = front;
        printf("Queue elements are");

        while (temp != NULL)
        {
            printf("%d ", temp->data); 
            temp = temp->next; 
        }
        printf("\n");
    }
}
// =================================================
int main() {

    int choice, value;
    char extra;

    while (1) {

        printf("\nChoose an operation:\n");
        printf("1. Enqueue (Insert)\n");
        printf("2. Dequeue (Delete)\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        // =================================================
          if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n') 
        {
            printf("Invalid input! Please enter digits only.\n");
            while (getchar() != '\n');
            continue;
        }
        // =================================================
        if (choice < 1 || choice > 4) 
        {
            printf("Invalid choice! Please enter 1 to 4.\n");
            continue;
        }


        // =================================================================================
        switch (choice)
        {
            case 1: {
                 int attempts = 0;
                do {
                    printf("Enter value to insert: ");
                    if (scanf("%d%c", &value, &extra) != 2 || extra != '\n') {

                        printf("Invalid input! Please enter a number.\n");
                        attempts++;
                        while (getchar() != '\n');
                        continue;
                    }
                    enqueue(value);
                    break;

                } while (attempts < 3);


                if (attempts == 3) {

                    printf("Three attempts finished. Returning to main menu.\n");
                }
                break;
            }
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
        }
    }
}

