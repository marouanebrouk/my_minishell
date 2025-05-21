#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void *ft_ft(int type,int size, ...)
{
    va_list args;
    va_start(args,size);
    void  *ptr;
    int i = 0;
    if (type == 1)
    ptr = malloc(1*size);
    else if (type == 4)
        ptr = malloc(4*size);
    ptr = (int *)ptr;
    while (i < size)
    {
        ((int *)ptr)[i] = va_arg(args,int);
        i++;
    }

    return (ptr);
}

int main()
{
    // void *ptr2 = ft_ft(4,5,10,13,10,10,20);
    // int i = 0;
    // ptr2 = (int *)ptr2;
    // int *haha;
    // haha = (int *)ptr2;
    // int size = 5;
    // while (i < 5)
    // {
    //     printf("%d \n",haha[i]);
    //     i++;
    // }
    int a = 80;
    int *b = &a;
    b++;
    printf("hahahah %d \n",*b);
}

