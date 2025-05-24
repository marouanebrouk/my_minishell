#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int flag = 0;

void ft_handler(int signum)
{
    static char c;
    static int bit_count = 0;
    if (signum == SIGUSR1)
        c = (c << 1) | 0;
    else if (signum == SIGUSR1)
        c = (c << 1) | 1;
    bit_count++;
    if (bit_count == 8)
    {
        write(1,&c,1);
        bit_count = 0;
        c = 0;
    }
}

int main()
{
    int pid = getpid();
    printf("pid is %d\n",pid);
    signal(SIGUSR1,ft_handler);
    signal(SIGUSR2,ft_handler);
    while (1)
        pause();
}