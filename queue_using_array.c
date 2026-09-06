#include <stdio.h>

#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

int isFull() {
    return rear == SIZE - 1;
}

int isEmpty() {
    return front == -1 || front > rear;  
}

//======================== 
void enqueue(int value) {
    if (isFull()) {
        printf("Queue is FULL! Cannot insert %d\n", value);
    }
    else {
        if (front == -1)    
            front = 0;      

        
        if (value >30 && value < 40)
            {
            printf("INVALID");
             }
        else {
        rear++;
            queue[rear] = value; // inserts the new value

            printf("%d inserted in the queue\n", value);
        }
        } 
    }


// =================================================
void dequeue() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
    }
    else
    {
        printf("%d  removed from the queue\n", queue[front]);
        front++;
    }
}



void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
    }
    else {
        printf("Queue elements are: ");

        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }

        printf("\n");
    }
}

// ==============================================================================

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


        
        if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n') {
            printf("Invalid input! Please enter digits only.\n");
            while (getchar() != '\n');
            continue;
        }

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