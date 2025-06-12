#include "mini.h"


//ls -l | grep a.out | wc -l
void call_pipe_engine(t_pipelist *pipelist, char **envp)
{
    int pipefd[2];
    int prev_read = -1;
    int pid;

    while (pipelist)
    {
        if (pipelist->next)
            pipe(pipefd);

        pid = fork();
        if (pid == 0)
        {
            if (prev_read != -1)
            {
                dup2(prev_read, STDIN_FILENO);
                close(prev_read);
            }
            if (pipelist->next)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

            char *path = ft_get_path_cmd(pipelist->value, envp);
            execve(path, pipelist->arguments, envp);
            perror("execve");
            exit(1);
        }
        else
        {
            if (prev_read != -1)
                close(prev_read);
            if (pipelist->next)
            {
                close(pipefd[1]);       // parent not writing
                prev_read = pipefd[0];  // k the read end for next command
            }
            waitpid(pid, NULL, 0);
            pipelist = pipelist->next;
        }
    }
}
