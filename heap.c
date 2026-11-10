#include <stdio.h>
#define MAX 100
int maxHeap[MAX], minHeap[MAX];
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
    i = maxSize;
    //when we insert then i = 7
    maxHeap[i] = value;
    //maxheap[7] = 60  inserting 60 in heap

    maxSize++;
    while (i > 0)//checking greater 
    {
        parent = (i - 1) / 2;
        if (maxHeap[parent] < maxHeap[i])
        {
            temp = maxHeap[parent];
            maxHeap[parent] = maxHeap[i];
            maxHeap[i] = temp;
            i = parent;
        }
        else
            break;
    }
    printf("Inserted into Max Heap.\n");
}
// DELETE FROM MAX HEAP
void deleteMax()
{
    int i = 0, left, right, largest, temp;
    if (maxSize == 0)
    {
        printf("Max Heap is empty!\n");
        return;
    }
    printf("Deleted: %d\n", maxHeap[0]);
    maxHeap[0] = maxHeap[maxSize - 1];
    maxSize--;
    while (1)
    {
        left = 2 * i + 1;
        right = 2 * i + 2;
        largest = i;
        if (left < maxSize && maxHeap[left] > maxHeap[largest])
            largest = left;
        if (right < maxSize && maxHeap[right] > maxHeap[largest])
            largest = right;
        if (largest != i)
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
    for (i = 0; i < maxSize; i++)
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
    i = minSize;
    minHeap[i] = value;
    minSize++;
    while (i > 0)
    {
        parent = (i - 1) / 2;
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
    int i = 0, left, right, smallest, temp;
    if (minSize == 0)
    {
        printf("Min Heap is empty!\n");
        return;
    }
    printf("Deleted: %d\n", minHeap[0]);
    minHeap[0] = minHeap[minSize - 1];
    minSize--;
    while (1)
    {
        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;
        if (left < minSize && minHeap[left] < minHeap[smallest])
            smallest = left;
        if (right < minSize && minHeap[right] < minHeap[smallest])
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
    for (i = 0; i < minSize; i++)
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
