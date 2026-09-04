
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
    // data next box is null    
    newNode->next = NULL;

    // ===
    if (front == NULL) {
        // first node becomes both front and rear
        front = newNode = rear;
        // rear = newNode; // only if one node is there

    } else {
        // basically connecting to next newnode 
        rear->next = newNode;
        rear = newNode;     // move rear to new node

    }

    printf("%d inserted in the queue\n", value);
}


// =================================================
// dequeue to remove element
//  here fifo = first in first out
void dequeue() {

    if (isEmpty()) {

        printf("Queue is EMPTY!\n");

    } else {

        // store the node which we want to remove
        struct Node *ptr = front;

        printf("%d removed from the queue\n", front->data);

        // move front to next node
        // front->data this data moved to new front node
        front = front->next;
        // if queue becomes empty
        if (front == NULL) {
            rear = NULL;
        }
      // free the removed node but still we renenber that
        free(ptr);
    }
}


// =================================================
// display queue

void display() {

    if (isEmpty()) {

        printf("Queue is EMPTY!\n");

    } 
    else {
// travel through liinked list
// temprory created temp and it is assigned to front
        struct Node *temp = front;
        printf("Queue elements are: ");

        while (temp != NULL) {

            printf("%d ", temp->data); //print this like here value present in current node

            temp = temp->next; // move to next value mean node
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
        // VALIDATION 1
        // check input of choice

        if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n') {
            printf("Invalid input! Please enter digits only.\n");
            while (getchar() != '\n');
            continue;
        }


        // =================================================
        // VALIDATION 2
        // check if choice is between 1-4

        if (choice < 1 || choice > 4) {

            printf("Invalid choice! Please enter 1 to 4.\n");
            continue;
        }


        // =================================================================================
        switch (choice) {

            case 1: {

                int attempts = 0;

                do {

                    printf("Enter value to insert: ");

                    // easy input validation
                    if (scanf("%d%c", &value, &extra) != 2 || extra != '\n') {

                        printf("Invalid input! Please enter a number.\n");
                        attempts++;
                        while (getchar() != '\n');
                        continue;
                    }


                    // =================================================
                    

                    if (value > 30 && value < 40) {

                        printf("INVALID\n");
                        attempts++;
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

