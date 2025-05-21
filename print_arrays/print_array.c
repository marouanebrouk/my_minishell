#include <unistd.h>
#include <stdio.h>

void	print_reverse(int *arr, int size)
{
    while (size)
    {
        --size;
        printf("%d \n",*(arr + size));
    }
}


void	print_until(char *arr, char stop)
{
    while(*arr)
    {
        if (*arr == stop)
            break;
        printf("%c", *arr);
        arr++;
    }
    printf("\n");
}



void	print_mirror(char *arr)
{
    // marouane
    char *pstart = NULL;
    char *pend = NULL;
    pstart = arr;
    pend = arr;
    while(*pend)
        pend++;
    pend--;
    while(pstart <= pend)
    {
        printf("%c",*pstart);
        if  (pstart != pend)
        {
            printf(" ");
            printf("%c",*pend);
        }
        printf("\n");
        pstart++;
        pend--;
    }
}



// this one prints array with no duplication

int duplicated(int value, int index, int *arr)
{
    int i = 0;
    while (i < index)
    {
        if (arr[i] == value)
            return 1;
        i++;
    }
    return 0;
}

void	print_unique(int *arr, int size)
{
    int i = 0;
    while (i < size)
    {
        if (!duplicated(arr[i],i,arr))
            {
                printf("%d ",arr[i]);
            }
        i++;
    }
    printf("\n");
}




int main()
{
    int arr[10] = {0,45,45,56,869,2,0,5,4,5};
    // char arr[7] = {'a','b','c','d','c','s','v'};
    // print_reverse(arr,6);                            check
    // print_until("helloMarouane",'M');  //               check
    // print_mirror(arr);                         //   check
    print_unique(arr,10);                            //  check
    // print_grouped_chars(char *arr);                  not check
    // print_spiral(int **matrix, int rows, int cols);  not check
}
