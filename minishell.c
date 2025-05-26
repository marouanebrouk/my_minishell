#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "mini.h"
#include <readline/readline.h>
#include <readline/history.h>

#define GREEN "\033[0;32m"
#define RESET "\033[0m"

t_redir *new_redirection(char *file, e_token token)
{
	t_redir *red;

	red = malloc(sizeof(t_redir));
	if (!red)
		return (NULL);
	red->type = token;
	red->file = file;
	red->data = NULL;
	red->next = NULL;
	return (red);
}

t_token *new_node(char *cmd, e_token type, t_redir *red)
{
	t_token *node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = cmd;
	node->rederiction = red;
	node->argument = NULL;
	node->next = NULL;
	return (node);
}

int		ft_is_sep(char		c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int is_redirection_or_pipe(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

e_token get_the_next_token(char *cmd, int i)
{
	while (cmd[i] && ft_is_sep(cmd[i]))
		i++;
	return (get_token(cmd[i], cmd[i + 1]));
}

int get_cmd_area(char *cmd, int start)
{
	int len = 0;
	int j = 0;

	while (cmd[start] && cmd[start] != '|' && cmd[start] != '<' && cmd[start] != '>')
	{
		if (cmd[start] == '"' || cmd[start] == '\'')
		{
			j = skip_quotes(cmd + start + 1, cmd[start]);
			len += j;
			start += j;
		}
		len++;
		start++;
	}
	return (len);
}

int is_redir_or_cmd(e_token tok)
{
	return (tok == NOT || tok == APPEND || tok == HERDOK || tok == IN || tok == OUT);
}

int     is_red(e_token      type)
{
	return (type == IN || type == OUT || type == APPEND || type == APPEND || type == HERDOK);
}


static int	is_see(char c, char *sep)
{
	if (ft_strchr(sep, c) != NULL)
		return (1);
	return (0);
}

char	*get_the_file(char *str, int *j, e_token tok)
{
	int		start;
	char	*substr;

	str[*j] = 127;
	if (tok == HERDOK || tok == APPEND)
		str[++(*j)] = 127;
	start = 0;
	while (str[*j] && str[*j] == ' ' || str[*j] == 127)
		(*j)++;
	start = *j;
    while (str[*j])
    {
        if (str[*j] == '"' || str[*j] == '\'')
            *j+= skip_quotes((str + *j + 1), str[*j]);
        if (get_token(str[*j], (str[*j + 1])) != NOT || get_token(str[*j], (str[*j + 1])) == END)
            break;
        (*j)++;
    }
	substr = ft_substr(str, start, *j - start);
	while (start < *j)
		str[start++] = 127;
	return (substr);
}

int	redir_check(char *cmd, int i)
{
	e_token	n;
	n = get_the_next_token(cmd, i);
	if (n != NOT)
		return (0);
	return (1);
}

int ft_check_syntax(e_token token, char *cmd, int i)
{
	e_token next;
	if (cmd[i] != '"' && cmd[i] != '\'')
		i++;
	if (token == HERDOK || token == APPEND)
		(i++);
	if (token == PIPE)
	{
		next = get_the_next_token(cmd, i);
		if (1 == i|| next == END || !(next == NOT || is_red(next)))
		{
			if (1 == i)
			{
				printf (SYNTAX_ERR);
				return (0);
			}
			else
			{
				printf (SYNTAX_ERR);
				return (0);
			}
		}
	}
	if (is_red(token))
	{
		int a = redir_check(cmd, i);
		if (!a)
		{
			printf (SYNTAX_ERR);
			return (0);
		}
	}
	return (1);
}

char		*handle_command(char *cmd, int		*i)
{
	char		*all_command;
	int		len = get_cmd_area(cmd, *i);
	all_command = ft_substr(cmd, *i, len);
	*i += len;
	return (all_command);
}

t_token *check_cmd_rederction(char *cmd, e_token token, int *i)
{
	t_redir *red;
	t_redir     *redir = NULL;
	red  = NULL;
	redir = NULL;
	char *filename;
	char *all_cmd;
	int j = *i;
	int length = 0;
	while (is_redir_or_cmd(token) && cmd[j])
	{
		if (!ft_check_syntax(token, cmd, j))
			return (NULL);
		if (token != NOT)
		{
			filename = get_the_file(cmd, &j, token);
			//printf ("the file name is %s\n", filename);
			red = new_redirection(filename, token);
			add_redir_back(red, &redir);
		}
		else
		{
			if (cmd[j] == '"' || cmd[j] == '\'')
				j += skip_quotes(cmd + j + 1, cmd[j]);
			j++;
		}
		token = get_token(cmd[j], cmd[j + 1]);
	}
	all_cmd = handle_command(cmd, i);
	return (new_node(all_cmd, NOT, redir));
}

t_token *tokenize(char *cmd)
{
    t_token *list = NULL;
    t_token *node = NULL;
    e_token token;
    int i = 0;
    while (cmd[i])
    {
        token = get_token(cmd[i], cmd[i + 1]);
        if (!ft_check_syntax(token, cmd, i))
            return (NULL);
        if (token == PIPE)
        {
            i++;
            node = new_node("|", token, NULL);
            while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n')
                i++;
        }
        else
            node = check_cmd_rederction(cmd, token, &i);
        if (!node)
            return (NULL);
        add_node_back(node, &list);
    }
    return (list);
}

void ft_print_redirection(t_redir *red)
{
	while (red) 
	{ 
		printf("file of rederction : [%s] type %d\n", red->file, red->type);
		red = red->next;
	}
}

void ft_print_token(t_token *token)
{
	while (token)
	{
		printf("TOKEN: [%s] type: %d argument %s\n", token->value, token->type, token->argument[1]);
		if (token->rederiction)
			ft_print_redirection(token->rederiction);
		token = token->next;
	}
}

int		ft_count(t_redir *tokens)
{
	int count;
	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

int		ft_lst_size(t_token *tokens)
{
	int count;
	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}




int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

int is_builtin(char *cmd)
{
    if (!ft_strcmp(cmd,"cd") || !ft_strcmp(cmd,"pwd") || !ft_strcmp(cmd,"echo") || !ft_strcmp(cmd,"exit") || !ft_strcmp(cmd,"export") || !ft_strcmp(cmd,"env")
            || !ft_strcmp(cmd,"unset"))
        return (1);
    return(0);
}


void	ft_handle_builtins(t_token *list)
{
	if (!ft_strcmp(list->value, "cd"))
	{
		if (!list->argument[1])
			write(2, "cd: missing argument\n",21);
		else if (chdir(list->argument[1]) != 0)
			perror("cd");
	}
	else if (!ft_strcmp(list->value, "pwd"))
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		else
			perror("pwd");
	}
	else if (!ft_strcmp(list->value, "echo"))
	{
		int i = 1;
		while (list->argument && list->argument[i])
		{
			printf("%s", list->argument[i]);
			if (list->argument[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else if (!ft_strcmp(list->argument[0], "exit"))
		exit(1);
}


void split_args_from_cmd(t_token *token)
{
    int i = 0;
    while (token)
    {
        if(token->type == NOT && token->value)
        {
            token->argument = ft_split(token->value,32);
            token->value = token->argument[0];
        }
        token = token->next;
    }
}

char *ft_get_path_cmd(t_token *list,char **envp)
{
    int i = -1;
    char **paths;
    paths = ft_split(getenv("PATH"),':');
    i = -1;
    while(paths[++i])
    {
        paths[i] = ft_strjoin(paths[i],"/");
        paths[i] = ft_strjoin(paths[i],list->value);
    }
    i = -1;
    while(paths[++i])
        if(access(paths[i], F_OK | X_OK) == 0)
            break;
    return (paths[i]);
}
void ft_execute_cmd(t_token *list, char **envp)
{
    int pid = 0;
    char *path_to_exec = ft_get_path_cmd(list, envp);
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
		//printf ("the arg is %s\n", list->argument[1]);
        if (execve(path_to_exec,list->argument,envp) == -1)
			printf ("command not found\n");
        exit(1);
    }
    wait(NULL);
}

void ft_general_exec(t_token *list,char **envp)
{
    split_args_from_cmd(list);
    if(is_builtin(list->value))
        ft_handle_builtins(list);
    else
        ft_execute_cmd(list,envp);  
}

char	*give_content(t_redir		*herdok)
{
	char		*line;
	char		*content;
	content = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		//printf ("the herdok file is%s\n", herdok->file);
		//int		a = ft_strncmp(line, herdok->file);
		//printf ("the line is %s\n", line);
		//printf ("%d\n", a);
		if (!line || ft_strcmp(line, herdok->file) == 0)
			break;
		content = ft_strjoin(content, ft_strjoin(line, "\n"));
	}
	return (content);
}

char 	*ft_herdok(t_redir *redr)
{
	char		*content;
	content = give_content(redr);
	return (content);
}

int	ft_heredok_file(char *data)
{
	int		fd;
	fd = open("/tmp/herdok.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	write(fd, data, ft_strlen(data));
	close(fd);
	return (fd);
}

int 		hanlde_herdok(t_token *node)
{
	t_redir		*red;
	while (node)
	{
		red = node->rederiction;
		while (red)
		{
			if (red->type == HERDOK)
			{
				red->data = ft_herdok(red);
				//printf ("the data is %s\n", red->data);
				red->fd = ft_heredok_file(red->data);
			}
			red = red->next;
		}
		node = node->next;
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	t_token *tokens;
	char *cmd;
	t_redir *list_of_reder = NULL;
	
	while (1)
	{
		cmd = readline(GREEN "minishell $ " RESET);
		if (!cmd)
		{
			write(1, "exit\n", 5);
			break;
		}
		cmd = ft_remove_space(cmd, SEP);
		if (!q_handler(cmd))
			printf (SYNTAX_ERR);
		if (ft_strlen(cmd))
			add_history(cmd);
		tokens = tokenize(cmd);
		hanlde_herdok(tokens);
		//rederction_handler(tokens);
		ft_general_exec(tokens,envp);
		//execution(tokens);
		// if (tokens)
		// 	ft_print_token(tokens);
	}
	return (0);
}