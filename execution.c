#include "mini.h"




t_redir *new_redirection(char *file, e_token token)
{
    t_redir *red;

    red = malloc(sizeof(t_redir));
    if (!red)
        return (NULL);
    red->type = token;
    red->file = file;
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

int is_redirection_or_pipe(char c)
{
    return (c == '<' || c == '>' || c == '|');
}

e_token get_the_next_token(char *cmd, int i)
{
    while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
        i++;
    return (get_token(cmd[i], cmd[i + 1]));
}

int get_cmd_area(char *cmd, int start)
{
    int len = 0;
    int j = 0;

    while (cmd[start] && get_token(cmd[start], cmd[start + 1]) == NOT)
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

int     check_synatx_error(e_token      type, char *cmd, int        i)
{
    e_token     next;
    if (type  == HERDOK || type == APPEND)
        i++;
    if (type == PIPE)
    {
        next = get_the_next_token(cmd, i);
        if (next != NOT)
        {
            printf ("SYNATAX ERROR PIPE WITHOT COMMAND\n");
            return (0);
        }
        i++;
    }
    return (1);
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
    while (str[*j] && ft_strchr(" \t\n\v\r\f\177", str[*j]))
        (*j)++;
    start = *j;
    while (str[*j])
    {
        if (str[*j] == '"' || str[*j] == '\'')
            *j+= skip_quotes((str + *j + 1), str[*j]);
        if (str[*j] == ' ' || get_token(str[*j], (str[*j + 1])) != NOT || get_token(str[*j], (str[*j + 1])) == END)
            break;
        (*j)++;
    }
    substr = ft_substr(str, start, *j - start);
    while (start < *j)
        str[start++] = 127;
    // printf ("substr : %s\n", substr);
    return (substr);
}

int	redir_check(char *cmd, int i)
{
    e_token	n;
    n = get_the_next_token(cmd, i);
    if (n != NOT || n == END)
        return (0);
    return (1);
}

int check_syntax(e_token token, char *cmd, int i)
{
    e_token next;
    if (cmd[i] != '"' && cmd[i] != '\'')
        i++;
    if (token == HERDOK || token == APPEND)
        (i++);
    //printf ("the value of i in the check syntax is %d\n", i);
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
                printf ("error pipe f lkher \n");
                return (0);
            }
        }
    }
    if (is_red(token))
    {
        if (!redir_check(cmd, i))
        {
            printf (SYNTAX_ERR);
            return (0);
        }
    }
    return (1);
}

t_token *check_all(char *cmd, e_token token, int *i)
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
        if (!check_syntax(token, cmd, j))
            return (NULL);
        if (token != NOT)
        {
            filename = get_the_file(cmd, &j, token);
            //printf ("the file of rederction is %s\n", filename);
            red = new_redirection(filename, token);
            add_redir_back(red, &redir);
        }
        else
        {
            if (cmd[j] == '"' || cmd[j] == '\'')
                j += skip_quotes(cmd + j + 1, cmd[j]);
            if (cmd[j] == ';')
            {
                printf ("synatx error\n");
                return (NULL);
            }
            j++;
        }
        token = get_token(cmd[j], cmd[j + 1]);    
    }
    length = get_cmd_area(cmd, *i);
    all_cmd = ft_substr(cmd, *i, length);
    //printf ("the cmd is %s\n", all_cmd);
    *i += length;
    //printf("the strlen of cmd is %d\n", length);
    t_token *cmd_node = new_node(all_cmd, NOT, redir);
    return (cmd_node);
}   

t_token *tokenize(char *cmd)
{
    t_token *list = NULL;
    t_token *node = NULL;
    e_token token;
    int i = 0;
    char        **arg;
    while (cmd[i])
    {
        token = get_token(cmd[i], cmd[i + 1]);
        //printf ("the type is %d\n", token);
        if (!check_syntax(token, cmd, i))
            return (NULL);
        if (token == PIPE)
        {
            i++;
            node = new_node("|", token, NULL);
            while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n')
                i++;
        }
        else
            node = check_all(cmd, token, &i);
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
        printf("TOKEN: [%s] type: %d\n ", token->value, token->type);
        if (token->rederiction)
            ft_print_redirection(token->rederiction);
        else
            printf("No redirections\n");
        token = token->next;
    }
}





// EXECUTION PHASE




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
//echo functiuon

int	echo_has_n_option(char *arg)
{
    int	i;
    
    i = 2;
    if (!arg || arg[0] != '-' || arg[1] != 'n')
        return (0);
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}



// int	ft_echo(t_token *list)
// {
//     int	i = 1;
//     int	newline = 1;

//     while (list->argument && list->argument[i] && echo_has_n_option(list->argument[i]))
//     {
//         newline = 0;
//         i++;
//     }
//     while (list->argument[i])
//     {
//         printf("%s", list->argument[i]);
//         if (list->argument[i + 1])
//             printf(" ");
//         i++;
//     }
//     if (newline)
//         printf("\n");
//     return (0);
// }


int	ft_echo(t_token *list)
{
	int	i = 1;
	int	newline = 1;

	while (list->argument && list->argument[i] && echo_has_n_option(list->argument[i]))
	{
		newline = 0;
		i++;
	}
	int j = 0;
	while (list->argument[i])
	{
		j = 0;
		while (list->argument[i][j])
		{
			if (list->argument[i][j] == '"')
				j++;
			else
			{
				printf("%c", list->argument[i][j]);
				j++;
			}
		}
		if (list->argument[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}



// end echo
// env
void ft_env(t_token *list, char **envp)
{
    (void)envp;
    int i = -1;
    extern char **environ;
    while(environ && environ[++i])
    printf("%s \n",environ[i]);
}
// end env

//builtin function

void	ft_handle_builtins(t_token *list, char **envp)
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
        ft_echo(list);
    else if (!ft_strcmp(list->value, "exit"))
    {
        printf("exit\n");
        exit(0);
    }
    else if (!ft_strcmp(list->value,"env"))
        ft_env(list,envp);
}
//end builtin function

// split args from cmd
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
// end split


int ft_count_commands(t_token *list)
{
    int count = 0;
    while (list)
    {
        if (list->type == NOT)
            count++;
        list = list->next;
    }
    return (count);
}

int ft_count_pipes(t_token *list)
{
    int count_pipes = 0;
    while(list)
    {
        if (list->type == PIPE)
            count_pipes++;
        list = list->next;
    }
    return (count_pipes);
}



void count(t_token *list)
{
    int count_commands = ft_count_commands(list);
    int count_pipes = ft_count_pipes(list);
    printf("there is %d commands \n",count_commands);
    printf("there is %d pipes \n",count_pipes);
}

char *ft_get_path_cmd(char *value, char **envp)
{
    int i;
    char **paths;
    char *tmp;
    char *full_path;
    i = -1;
    paths = ft_split(getenv("PATH"),':');
    if (!paths)
        return (NULL);

    i = 0;
    while(paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, value);
        free(tmp);
        free(paths[i]);
        paths[i] = full_path;
        i++;
    }
    i = 0;
    while(paths[i])
    {
        if(access(paths[i], F_OK | X_OK) == 0)
            break;
        i++;
    }
    return (paths[i]);
}

void ft_execute_cmd(t_token *list, char **envp)
{
        int pid = 0;
        char *path_to_exec = ft_get_path_cmd(list->value, envp);
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            execve(path_to_exec, list->argument, envp);
            printf("command not found : %s \n",list->argument[0]);
            exit(1);
        }
        else
            wait(NULL);
}


int is_there_pipe(t_token *list)
{
    while(list)
    {
        if (list->type == PIPE)
            return (1);
        list = list->next;
    }
    return (0);
}



void ft_general_exec(t_token *list,char **envp)
{
    int commands = ft_count_commands(list);
    printf("number of commands are %d \n",commands);
    // split_args_from_cmd(list);
    arahna(list);
    split_args_from_cmd(list);
    // get_node_args(list);
    // count(list);
    arahna(list);
    exit(1);
    if(is_builtin(list->value))
        ft_handle_builtins(list,envp);
    else
        ft_execute_cmd(list,envp);
}





void arahna(t_token *list)
{
    int i = 0;
    while (list)
    {
        printf("token is [%s]  type : [%d] \n",list->value,list->type);
        list = list->next;
    }
    printf("-----end of list-----\n");
}

// "here i print the node arguments after spliting them"
// void get_node_args(t_token *list)
// {
//     int i = 0;
//     printf("Arguments of each node ...\n");
//     while (list)
//     {
//         i = 0;
//         printf("value is %s \n",list->value);
//         while (list->argument && list->argument[i])
//         {
//             printf("argument %d %s \n",i,list->argument[i]);
//             i++;
//         }
//         list = list->next;
//     }
// }






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
        cmd = readline(GREEN "bash$ " RESET);
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
        // if (tokens)
        // {
        //      arahna(tokens);
            // ft_print_token(tokens);
        // }
        if (tokens != NULL)
            ft_general_exec(tokens,envp);




        // t_redir     *red = tokens->rederiction;
        // ft_print_redirection(red);
        // if (!tokens->rederiction->next->file)
        //     printf ("NULL\n");
        //printf ("the file is %s\n", tokens->rederiction->next->file);
    }
    return (0);
}
