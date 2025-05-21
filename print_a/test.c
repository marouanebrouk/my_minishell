#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>




int ft_swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}


int f()
{
    static int var;
    var += 1;
    printf("%d \n",var);
    return (var);
}

int main()
{
    f();
    f();
    f();
}