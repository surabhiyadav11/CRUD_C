#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int data;
    struct Node *next;
};

struct Node *top = NULL;

int isEmpty() 
{
    return top == NULL;
}

void push(int value) 
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->next = top;
    top = newNode;

    printf("%d pushed into the stack\n", value);
}

void pop()
{
    if (isEmpty())
    {
        printf("Stack is EMPTY!\n");
    } 
    else 
    {
        struct Node *temp = top;
        printf("%d popped from the stack\n", top->data);
        top = top->next;
        free(temp);
    }
}

void display() 
{
    if (isEmpty()) 
    {
        printf("Stack is EMPTY!\n");
    } 
    else
    {
        struct Node *temp = top;
        printf("Stack elements are: ");
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
         printf("\n");
    }
}

int main() {
    int choice, value;
    char extra;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Push (Insert)\n");
        printf("2. Pop (Delete)\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n') 
        {
            printf("Invalid input! Please enter digits only.\n");
            while (getchar() != '\n');
            continue;
        }


        if (choice < 1 || choice > 4) 
        {
            printf("Invalid choice! Please enter 1 to 4.\n");
            continue;
        }

        switch (choice) 
        {

            case 1:
                printf("Enter value to insert: ");

                if (scanf("%d%c", &value, &extra) != 2 || extra != '\n') 
                {
                    printf("Invalid input! Please enter a number.\n");
                    while (getchar() != '\n');
                    continue;
                }

                push(value);
                break;

            case 2:
                pop();
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

