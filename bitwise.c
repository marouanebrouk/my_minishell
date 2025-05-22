#include <stdio.h>
#include <signal.h>

int main() {
    char a;
    scanf("%c",&a);
    int i = 8;
    while(--i >= 0)
    {
        if (((a >> i) & 1) == 0)
            printf("0");
        else
            printf("1");
    }
    printf("\n");
    return 0;
}