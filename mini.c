#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>


#define MAX_INPUT 1024
#define MAX_ARGS 100


int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i]-s2[i]);
}


int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "exit"));
}

void	handle_builtin(char **args)
{
	if (!ft_strcmp(args[0], "cd"))
	{
		if (!args[1])
			write(2, "cd: missing argument\n",21);
		else if (chdir(args[1]) != 0)
			perror("cd");
	}
	else if (!ft_strcmp(args[0], "pwd"))
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		else
			perror("pwd");
	}
	else if (!ft_strcmp(args[0], "echo"))
	{
		int i = 1;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else if (!ft_strcmp(args[0], "exit"))
		exit(1);
}

void	run_command(char *input)
{
	char	*args[MAX_ARGS];
	char	*token;
	int		i = 0;
	int	pid;

	// Split input into arguments
	token = strtok(input, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return ;

	if (is_builtin(args[0]))
		handle_builtin(args);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
			wait(NULL);
		else
			perror("fork");
	}
}


int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("mini-shell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		run_command(input);
		free(input);
	}
	return (0);
}
