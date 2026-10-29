#include<stdio.h>
#define MAX 10
int a[MAX];
int n = 0;

void insertelement()
{
    int value;
    if(n == MAX)
    {
        printf("ARRAY IS FULL\n");
        return;
    }

    printf("enter the element\n");
    scanf("%d", &value);

    a[n] = value;
    n++;

    printf("element inserted\n");
}

void updateelement()
{
    int value, pos;
    if ( n == 0)
    {
        printf("aray is empty\n");
        return;
    }

    printf("enter idx no to update\n");
    scanf("%d", &pos);

    if(pos < 0 || pos >= n)
    {
        printf("invalid index\n");
        return;
    }

    printf("enter new value\n");
    scanf("%d", &value);

    a[pos] = value;

    printf("element updated\n");
}

void deleteelement()
{
    int pos, i;

    if(n == 0)
    {
        printf("array is empty\n");
        return;
    }

    printf("enter idx no to delete\n");
    scanf("%d", &pos);

    if(pos < 0 || pos >= n)
    {
        printf("invalid index\n");
        return;
    }

    for(i = pos; i < n-1; i++)
    {
        a[i] = a[i+1];
    }

    n--;

    printf("element deleted\n");
}

// void readelement()
// {
//     int i;

//     if(n == 0)
//     {
//         printf("array is empty\n");
//         return;
//     }

//     printf("array elements are\n");

//     for(i = 0; i < n; i++)
//     {
//         printf("%d ", a[i]);
//     }

//     printf("\n");
// }

void linearsearch()
{
    int value, i;

    if(n == 0)
    {
        printf("array is empty\n");
        return;
    }

    printf("enter value to search\n");
    scanf("%d", &value);

    for (i=0; i<n; i++)
    {
        if(a[i] == value)
        {
            printf("value found at this index = %d\n", i);
            return;
        }
    }

    printf("NOT FOUND\n");
}

void binarySearch()
//a[]= 10 20 30 40 50 60 70
//     0  1  2  3  4  5  6
{
    int value, low, high, mid;
    //value = element want to finad
    // low = idx of first element in current search range
    // high = idx of last element in current search range
    // mid idx of middle element

    if(n == 0)
    {
        printf("array is empty\n");
        return;
    }

    printf("enter value to search\n");
    scanf("%d", &value);//60

    low = 0;//low=0
    high = n - 1;//high=7-1=6

    while(low <= high)//0<6
    {
        mid = (low + high) / 2; //mid = 3 == 40

        if(a[mid] == value)//if 60 == 40 ======no
        {
            printf("value found at this index = %d\n", mid);
            return;
        }
        else if(value < a[mid]) //60< 40 =======no
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    printf("NOT FOUND\n");
}

int main ()
{
    int choice;

    do
    {
        printf("\n---MENU IS---\n");
        printf("1. insert element in array\n");
        printf("2. update the element\n");
        printf("3. delete the element\n");
        printf("4. linear search\n");
        printf("5. binary search\n");
        printf("6. display array\n");
        printf("7. exit\n");

        printf("enter in bet 1-7\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insertelement();
                break;
            case 2:
                updateelement();
                break;
            case 3:
                deleteelement();
                break;
            case 4: 
                linearsearch();
                break;
            case 5:
                binarySearch();
                break;
            case 6:
                readelement();
                break;
            case 7:
                printf("exit the programme\n");
                break;
            default:
                printf("invalid choice\n");
        }
    }while (choice != 7);

return 0;
}