#include <stdio.h>
#include <unistd.h>
#include <signal.h>


#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>





void ft_send_bit(char c,int pid)
{
    int i = 8;

    while (--i >= 0)
    {
        if (((c >> i) & 1) == 0)
        {
            if(kill(pid, SIGUSR1) == -1)
                printf("SIGUSR1 NOT SEND");
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
                printf("SIGUSR1 NOT SEND");
        }
    }
    // usleep(1300);
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
        ft_send_message(av[2],pid);
    }
    else
        printf("error in arguments\n");
}
