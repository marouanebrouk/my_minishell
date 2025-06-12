#include "mini.h"

void call_pipe_engine(t_pipelist *pipelist, char **envp)
{
    int pipefd[2];
    int prev_read = -1;
    int i = 0;
    pid_t pids[100];

    while (pipelist)
    {
        if (pipelist->next)
            pipe(pipefd);

        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (prev_read != -1)
            {
                dup2(prev_read, STDIN_FILENO);
                close(prev_read);
            }

            if (pipelist->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }

            execve(ft_get_path_cmd(pipelist->value, envp), pipelist->arguments, envp);
            perror("execve failed");
            exit(1);
        }

        // parent continues here
        if (prev_read != -1)
            close(prev_read);

        if (pipelist->next)
        {
            close(pipefd[1]);
            prev_read = pipefd[0];
        }

        pipelist = pipelist->next;
        i++;
    }

    // wait for all children AFTER loop
    while (--i >= 0)
        waitpid(pids[i], NULL, 0);
}
