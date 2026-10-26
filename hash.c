#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
struct Node
{
    int data;
    struct Node *next;
};

struct Node *hashTable[SIZE] = {NULL};
// HASH FUNCTION
int hashFunction(int key)
{
    //key=22 mod 10
    return ((key % SIZE) + SIZE) % SIZE;
    //     ((22%10) + 10) % 10;
    //      (2+ 10) % 10;
    // return 2;

}

// INSERT
//12,22,32
void insert(int value)
{
    int index = hashFunction(value);
    //it calculates the mod vlaue // 2,2,2
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    //initially hash table is null
 
    newNode->data = value;
    //newNode->data = 12//idx===2

     // Add node at the beginning of linked list
    //connecting newnode to existing list
    newNode->next = hashTable[index];
    //newNode->next = hashtable[2]
    //hashtable[2] = null
    //therefore== newnode->next=null
   
    hashTable[index] = newNode;
    //hashtable[2] = 12 
    //next==null
    printf("Value inserted successfully.\n");
}

// SEARCH
void search(int key)
{
    int index = hashFunction(key);
    struct Node *temp = hashTable[index];
// index 2 == 32 - 22 - 12 -null
//index 5 == 15 - null
//search for 22
    while (temp != NULL)//temp starts at 1st node of idx 2
    // initially temp = 32
    {
        if (temp->data == key)
        {
            printf("Value found at index %d.\n", index);
            return;
        }

        temp = temp->next;
    }

    printf("Value not found.\n");
}

// DELETE
void deleteNode(int key)
//hashtable[2] == 32 - 22 - 12 
{
    int index = hashFunction(key);
    struct Node *temp = hashTable[index];
    struct Node *prev = NULL;

    while (temp != NULL)
    {
        if (temp->data == key)
        {
            if (prev == NULL)//deleting first node
                hashTable[index] = temp->next;//this makes hashtable[2] point to directly 22
            else//deleting middle or last
                prev->next = temp->next;
                // 32 to 22  = /points to 12
                //we change link 32 directly points to 12

            free(temp);
            printf("Value deleted successfully.\n");
            return;
        }
// when current value does not match 
//initially temp =32
        prev = temp;
        //prev=32
        temp = temp->next;
        //noe temp moves to 22
    }

    printf("Value not found.\n");
}

// UPDATE
void update(int oldValue, int newValue)
//hashtable[2] == 32 - 22 - 12 
//update 22 to 45
{
    int index = hashFunction(oldValue);
    struct Node *temp = hashTable[index];

    while (temp != NULL)
    {
        if (temp->data == oldValue)
        {
            if (oldValue == newValue)
            {
                printf("Both values are same.\n");
                return;
            }

            deleteNode(oldValue);
            insert(newValue);

            printf("Value updated successfully.\n");
            return;
        }

        temp = temp->next;
    }

    printf("Value not found. Update failed.\n");
}

// DISPLAY
void display()
{
    int i;
    struct Node *temp;

    for (i = 0; i < SIZE; i++)//loop visiting from 0 to 9
    {
        printf("Index %d: ", i);
        temp = hashTable[i];

        while (temp != NULL)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

// MAIN
int main()
{
    int choice, value, newValue;

    while (1)
    {
        printf("\n1. Insert\n");
        printf("2. Search\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(value);
                break;

            case 3:
                printf("Enter old value: ");
                scanf("%d", &value);
                printf("Enter new value: ");
                scanf("%d", &newValue);
                update(value, newValue);
                break;

            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteNode(value);
                break;

            case 5:
                display();
                break;

            case 6:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
