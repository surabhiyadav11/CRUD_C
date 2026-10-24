#include <stdio.h>
#define MAX 100
int maxHeap[MAX + 1], minHeap[MAX + 1];
int maxSize = 0, minSize = 0;
// INSERT INTO MAX HEAP
void insertMax()
{
    int value, i, parent, temp;
   //i index currently working
    // parent= index of current node s parent 
    //temp temprory  stores value when we swap two values 
    if (maxSize == MAX)
    {
        printf("Max Heap is full!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);
    //before inserting heap contains 6 maxsize = 6
    i = maxSize + 1;
    //when we insert then i = 7
    maxHeap[i] = value;
    //maxheap[7] = 60  inserting 60 in heap
    maxSize++;
    while (i > 1)//checking greater i>1
    {
        parent = i / 2; //   7/2=3
        if (maxHeap[parent] < maxHeap[i])
        //     idx 3 < idx 7
        // 30(parent of 60 newnode) < 60
        {
            temp = maxHeap[parent];//temp=30
            maxHeap[parent] = maxHeap[i];//idx 3 gets 60
            maxHeap[i] = temp;// idx 7 gets 30 
            i = parent;// i=3
        }
        else
            break;
    }
    printf("Inserted into Max Heap.\n");
}
// DELETE FROM MAX HEAP
void deleteMax()
{
    int i = 1, left, right, largest, temp;
// i=1 starts at root only
// left = idx of left child
//right = idx of right child
//largest== stores idx of largest among current node and its children
//temp== temporarily stores value while swapping
    if (maxSize == 0)
    {
        printf("Max Heap is empty!\n");
        return;
    }
    printf("Deleted: %d\n", maxHeap[1]);//60 deletes// as it is largest node

    maxHeap[1] = maxHeap[maxSize];
    //maxheap[1] = maxheap[6]

    maxSize--;
    //size changes from 6 to 5 
    //heap has 5 elemensts root got deleted and 25 went there 

    while (1)
    {
        //initially i = 1
        left = 2 * i;// left = 2 == 40 
        right = 2 * i + 1; // right = 3 == 50 
        largest = i;

        if (left <= maxSize && maxHeap[left] > maxHeap[largest])
            largest = left;
        // 2 <= maxsiz2 && 40 child > 25largest
        // 2<= 5 && 40 > 25
        // falseee
        //soo largest= left... 

        if (right <= maxSize && maxHeap[right] > maxHeap[largest])
            largest = right;
        // 3 <= 5 && 50 > 25
        // trueee

        if (largest != i)
        //currently idx 3 != 1
        //swappp
        {
            temp = maxHeap[i];
            maxHeap[i] = maxHeap[largest];
            maxHeap[largest] = temp;
            i = largest;
        }
        else
            break;
    }
}

// DISPLAY MAX HEAP
void readMax()
{
    int i;

    if (maxSize == 0)
    {
        printf("Max Heap is empty!\n");
        return;
    }

    printf("Max Heap: ");

    // i=1; i <= 5; i++
    for (i = 1; i <= maxSize; i++)
        printf("%d ", maxHeap[i]);

    printf("\n");
}

// INSERT INTO MIN HEAP
void insertMin()
{
    int value, i, parent, temp;

    if (minSize == MAX)
    {
        printf("Min Heap is full!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    i = minSize + 1;
    minHeap[i] = value;
    minSize++;

    while (i > 1)
    {
        parent = i / 2;
        if (minHeap[parent] > minHeap[i])
        {
            temp = minHeap[parent];
            minHeap[parent] = minHeap[i];
            minHeap[i] = temp;
            i = parent;
        }
        else
            break;
    }

    printf("Inserted into Min Heap.\n");
}

// DELETE FROM MIN HEAP
void deleteMin()
{
    int i = 1, left, right, smallest, temp;

    if (minSize == 0)
    {
        printf("Min Heap is empty!\n");
        return;
    }

    printf("Deleted: %d\n", minHeap[1]);

    minHeap[1] = minHeap[minSize];
    minSize--;

    while (1)
    {
        left = 2 * i;
        right = 2 * i + 1;
        smallest = i;

        if (left <= minSize && minHeap[left] < minHeap[smallest])
            smallest = left;

        if (right <= minSize && minHeap[right] < minHeap[smallest])
            smallest = right;

        if (smallest != i)
        {
            temp = minHeap[i];
            minHeap[i] = minHeap[smallest];
            minHeap[smallest] = temp;
            i = smallest;
        }
        else
            break;
    }
}

// DISPLAY MIN HEAP
void readMin()
{
    int i;

    if (minSize == 0)
    {
        printf("Min Heap is empty!\n");
        return;
    }

    printf("Min Heap: ");

    for (i = 1; i <= minSize; i++)
        printf("%d ", minHeap[i]);

    printf("\n");
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- HEAP MENU ---");
        printf("\n1. Insert into Max Heap");
        printf("\n2. Delete from Max Heap");
        printf("\n3. Display Max Heap");
        printf("\n4. Insert into Min Heap");
        printf("\n5. Delete from Min Heap");
        printf("\n6. Display Min Heap");
        printf("\n7. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insertMax();
                break;

            case 2:
                deleteMax();
                break;

            case 3:
                readMax();
                break;

            case 4:
                insertMin();
                break;

            case 5:
                deleteMin();
                break;

            case 6:
                readMin();
                break;

            case 7:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
