#include "mini.h"

void ft_printf(void *ptr)
{
    printf ("dyali %p\n", ptr + 10);
}

int main()
{
    int c = 76;
    int *p = &c;
    int **p2 = &p;
    int ***p3 = &p2;
    int ****p4 = &p3;
    printf("1. c = %u\n", &c);
    printf("2. p = %u\n", &p);
    printf("3. p2 = %u\n", &p2);
    printf("4. p3 = %u\n", &p3);
    printf("5. p4 = %p\n", p4);
    ft_printf(&c);
}
