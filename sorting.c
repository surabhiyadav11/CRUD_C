#include <stdio.h>
#define MAX 100
int a[MAX];
int n = 0;
// INSERT ELEMENT
void insertElement()
{
    int value;
    if (n == MAX)
    {
        printf("Array is full.\n");
        return;
    }

    printf("Enter element: ");
    scanf("%d", &value);

    a[n] = value;
    //a[3] = 30
    n++;
    //n becomes 4

    printf("Element inserted.\n");
}

// UPDATE ELEMENT
void updateElement()
{
    int pos, value;
    //pos position of element want to change
    //value = new value
    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    printf("Enter position to update: ");
    scanf("%d", &pos);
//we change value according to from position 
//chack less then 1 || cheks greater than 1
    if (pos < 1 || pos > n)
    {
        printf("Invalid position.\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &value);

    a[pos - 1] = value;
//User enters position	C array index	Element
//                 1	         0	        10
//                 2	         1	        20
//                 3	         2	        30
//                 4	         3          40

// if user enters pos 2 they mean 20
//but in C stored at 1 soo a[2-1] = value

    //replaces old element with new one

    printf("Element updated.\n");
}

// DELETE ELEMENT
void deleteElement()
{
    int pos, i;

    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    printf("Enter position to delete: ");
    scanf("%d", &pos);

    if (pos < 1 || pos > n)
    {
        printf("Invalid position.\n");
        return;
    }

    for (i = pos - 1; i < n - 1; i++)
    {
        a[i] = a[i + 1];
    }

    n--;

    printf("Element deleted.\n");
}

// DISPLAY ARRAY
void displayArray()
{
    int i;

    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    printf("Array: ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");
}

// BUBBLE SORT
void bubbleSort()
{
    int i, j, temp;

    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    for (i = 0; i < n - 1; i++)//if n=4 loop runs 3 passes
    {
        for (j = 0; j < n - 1 - i; j++)//compare adjacent elemnets
        {
            if (a[j] > a[j + 1])//compare two elements current and next of current
            {
                temp = a[j];//store in temp
                a[j] = a[j + 1]; //swap
                a[j + 1] = temp;// store new value
            }
        }
    }

    printf("Array sorted using Bubble Sort.\n");
}

// MERGE FUNCTION
//[10 20 30 40] mid= ending index of left part
//lb = 0. mid = 1. ub = 3

void merge(int lb, int mid, int ub)// 0, 1, 3
{
    int b[MAX];//temprory array to stire merged result
    int i = lb, j = mid + 1, k = lb;
    //    = 0     = 2         tells us where to store next elemnt in b
    // i = for one loop
    // j = for another loop
    // k= for merged loop
    while (i <= mid && j <= ub)//both array have elemnts
    {

        // i == 1 5 8 15 24
        // j == 3 10 16 20
        // k == comnination of i&j comparison
        if (a[i] < a[j]) // 1 < 3
        {
            b[k] = a[i];//put 1 in b array 
            i++; //increses i from first array
        }
        else
        {
            b[k] = a[j]; 
            j++;// increses j from second array 
        }
        k++;//k increses
    }
    //copy any remaining left elements
    while (i <= mid)//if j reached to it limit //all arrray i is at end 
    {
        b[k] = a[i];//simply copy all values of a in b
        i++;
        k++;
    }
    while (j <= ub)//all arrray i is at end 
    {
        b[k] = a[j];//simply copy all values a of j in b
        j++;
        k++;
    }
    for (i = lb; i <= ub; i++)//bcoz sorted array to in main array original
    {
        a[i] = b[i];//alll values 
    }
}

// MERGE SORT
void mergeSort(int lb, int ub)
//a = [40, 10, 30, 20]
//(0,3)// lb=0//ub=3
{
    int mid;
    if (lb < ub)//0<3 true
    {
        mid = (lb + ub) / 2;
        // 0+3 / 2 == 3/2 == 1

        //so [40, 10] && [30, 20]

        mergeSort(lb, mid);
        mergeSort(mid + 1, ub);
        merge(lb, mid, ub);
    }
}

void selectionSort()
//a[0]=30;
//a[1]=10
//a[2]=20
//n=3
{
    int i, j, min, temp;
    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }
    for (i = 0; i < n - 1; i++)
    {
        min = i;//assume a[0] is the smallest element
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
            //first comparison
            //10<30 == true
            //so min is 1
            {
                min = j;
            }
        }
        //swapping normal code here smallest with another one
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
    printf("Array sorted using Selection Sort.\n");
}
void insertionSort()
{
    int i, j, temp;
    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }
    // 4  5  10 1  6  2  array
    // 0  1  2  3  4  5 idx
    for (i = 1; i < n; i++)
    //i=2 
    {
        temp = a[i]; //temp = a[10]
        j = i - 1;//j=2-1 == 1
        // j-1 = 1 will start from 1
        while (j >= 0 && a[j] > temp)//a[j]=1 andd temp=10
        //j=1 > 1 &&  5 > 10 
        // true && false === false
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;//a[j+1] == j[1+1] == 2
        //so temp will be j[2] == 10
    }
    printf("Array sorted using Insertion Sort.\n");
}

int partition(int lb, int ub)
// 30 10 40 20
// 0  1  2  3
{
    int pivot, i, j, temp;
    pivot = a[lb];// pivot=a[lb] = 30
    i = lb + 1; // 10
    j = ub; // 20

    while (i <= j)
    {
        while (i <= ub && a[i] <= pivot)//move i from left
        //      1 <=3 && 1<= pivot i.e 10<=30 === truee
            i++;// makes i=2

        while (a[j] > pivot)// move j from right
        //20 > 30 ===== false
            j--;// now j=3

        if (i < j)//swapping
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    temp = a[lb];
    a[lb] = a[j];
    a[j] = temp;

    return j;
}

void quickSortRecursive(int lb, int ub)//(0,3)
{
    int pi;// idx where pivot is placed after partioning
// 30 10 40 20
// 0  1  2  3
    if (lb < ub)//0<3 truee
    {
        pi = partition(lb, ub);

        quickSortRecursive(lb, pi - 1);
        quickSortRecursive(pi + 1, ub);
    }
}

void quickSort()
{
    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    quickSortRecursive(0, n - 1);

    printf("Array sorted using Quick Sort.\n");
}

// MAIN FUNCTION
int main()
{
    int choice;

    do
    {
        printf("\n===== ARRAY MENU =====\n");
        printf("1. Insert element\n");
        printf("2. Update element\n");
        printf("3. Delete element\n");
        printf("4. Display array\n");
        printf("5. Bubble Sort\n");
        printf("6. Merge Sort\n");
        printf("7. selection sort\n");
        printf("8. insertion sort\n");
        printf("9. quick sort\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insertElement();
                break;

            case 2:
                updateElement();
                break;

            case 3:
                deleteElement();
                break;

            case 4:
                displayArray();
                break;

            case 5:
                bubbleSort();
                displayArray();
                break;

            case 6:
                if (n == 0)
                {
                    printf("Array is empty.\n");
                }
                else
                {
                    mergeSort(0, n - 1);
                    printf("Array sorted using Merge Sort.\n");
                    displayArray();
                }
                break;
            case 7: 
                    selectionSort();
                    break;

            case 8: 
                    insertionsort();
                    break;

            case 9: 
                    quicksort();
                    break;
        
            case 10:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}
