#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>





void ft_send_bit(char c,int pid)
{
    int i = 8;

    while (--i >= 0)
    {
        if (((c >> i) & 1) == 0)
        {
            if(kill(pid, SIGUSR1) == -1)
                exit(write(2,"SIG1 NOT SEND\n",14));
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
                exit(write(2,"SIG2 NOT SEND\n",14));
        }
    usleep(1000);
    }
}

void ft_send_message(char *str,int pid)
{
    int i = 0;

    while(str[i])
    {
        ft_send_bit(str[i],pid);
        i++;
    }
    ft_send_bit('\n',pid);
    ft_send_bit('\0',pid);
}


int main(int ac, char **av)
{
    // ./client PID "message";
    if (ac == 3)
    {
        int pid = atoi(av[1]);
        if (pid <= 0)
            return (printf("W9 \n"));
        ft_send_message(av[2],pid);
    }
    else
        printf("error in arguments\n");
}
