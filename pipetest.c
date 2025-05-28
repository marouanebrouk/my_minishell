

// pipe engine


// void	execute_pipeline(char ***cmds, int count)
// {
// 	int		i = 0;
// 	int		pipes[1024][2];
// 	pid_t	pid;

// 	while (i < count - 1)
// 	{
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			perror("pipe");
// 			exit(1);
// 		}
// 		i++;
// 	}

// 	i = 0;
// 	while (i < count)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(1);
// 		}

// 		if (pid == 0) // child
// 		{
// 			if (i > 0)
// 				dup2(pipes[i - 1][0], STDIN_FILENO); // read from prev pipe
// 			if (i < count - 1)
// 				dup2(pipes[i][1], STDOUT_FILENO); // write in next pipe

// 			// close all pipes
// 			int j = 0;
// 			while (j < count - 1)
// 			{
// 				close(pipes[j][0]);
// 				close(pipes[j][1]);
// 				j++;
// 			}

// 			execvp(cmds[i][0], cmds[i]);
// 			perror("exec");
// 			exit(1);
// 		}
// 		i++;
// 	}

// 	// parent: close all and wait
// 	i = 0;
// 	while (i < count - 1)
// 	{
// 		close(pipes[i][0]);
// 		close(pipes[i][1]);
// 		i++;
// 	}

// 	i = 0;
// 	while (i < count)
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// }
