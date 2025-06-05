#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>


int ft_test(int size, char *c, ...)
{
    va_list args;
    va_start(args,c);
    int i = 0;
    int sum = 0;
    while (i < size)
    {
        if (*c == '-')
            sum = sum - va_arg(args, int);
        else if (*c == '+')
            sum += va_arg(args, int);
        else if (*c == '/')
            sum /= va_arg(args, int);
        else if (*c == '*')
            sum *= va_arg(args, int);
        i++;
    }
    va_end(args);
    return (sum);
}

int main()
{
    int result = ft_test(5,"*",30,1,1,1,1);
    printf("%d \n",result);
}