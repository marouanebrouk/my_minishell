#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
        if (get_token(str[*j], (str[*j + 1])) != NOT || get_token(str[*j], (str[*j + 1])) == END)
            break;
        (*j)++;
    }
	substr = ft_substr(str, start, *j - start);
	while (start < *j)
		str[start++] = 127;
    printf ("substr : %s\n", substr);
	return (substr);
}

int	redir_check(char *cmd, int i)
{
	e_token	n;
	n = get_the_next_token(cmd, i);
    printf ("%d\n", n);
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
        printf("TOKEN: [%s] type: %d arg %s\n ", token->value, token->type, token->argument);
        if (token->rederiction)
            ft_print_redirection(token->rederiction);
        else
            printf("No redirections\n");
        token = token->next;
    }
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
        if (tokens)
            ft_print_token(tokens);
        // t_redir     *red = tokens->rederiction;
        // ft_print_redirection(red);
        // if (!tokens->rederiction->next->file)
        //     printf ("NULL\n");
        //printf ("the file is %s\n", tokens->rederiction->next->file);
    }
    return (0);
}