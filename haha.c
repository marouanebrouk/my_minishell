#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void *ft_ft(int type, int size, ...)
{
    va_list args;
    va_start(args,size);

    void *ptr;
    ptr = malloc(type * size);
    

    int i = 0;
    while (i < size)
    {
        if (type == 4)
            ((int *)ptr)[i] = va_arg(args,int);
        else if (type == 1)
            ((char *)ptr)[i] = va_arg(args,int);
        i++;
    }
    va_end(args);
    return (ptr);
}
#include <sys/wait.h>
int main()
{
    // // void *ptr2 = ft_ft(1,3,'c','z','d');
    // void *ptr2 = ft_ft(4,6,521,12,312,456,4986,26);
    // int i = 0;
    
    // int size = 5;
    // while (i < 6)
    // {
    //     printf("%d \n",((int*)ptr2)[i]);
    //     i++;
    // }

    int pid;
    // pid = fork();
    int n ;
    if (pid == 0)
    {
        n = 1;
    }
    else
    {
        n = 6;
    }
    for (int i = n; i < n + 5; i++)
    {
        printf("%d \n",i);
    }
    // wait(NULL);
    return 0;
}