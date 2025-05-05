#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#define SEP " \t\n"
# define SYNTAX_ERR		"bash: syntax error near unexpected token\n "
#ifndef MINI_H
#define MINI_H
typedef     enum  s_token
{
    PIPE,
    IN,
    OUT,
    APPEND,
    HERDOK,
    NOT, 
    END
}e_token;

typedef struct      s_redirection
{
    e_token     type;
    char        *file;
    struct  s_redirection *next;
}t_redir;

typedef struct  b_token
{
    e_token type;
    char        *value;
    char        **argument;
    t_redir *rederiction;
    struct  b_token *next;
}t_token;


// typedef struct s_cmd
// {
//     char        **args;         // Full argv-like array: {"grep", "txt", NULL}
//     t_redir     *redirs;
//     int         pipe_in;        
//     int         pipe_out;       
//     struct s_cmd *next;         // Next command in the pipeline
// }   t_cmd;

char	**ft_split(char *str, char charset);
char	*ft_strchr(const char	*s, int c);
int     ft_strlen(char *str);
char *get_next_line(int fd);
int     is_set(char c, char *set);
char        *ft_remove_space(char   *s1, char *set);
void        ft_check_synatx_error(char     *line);
int     q_handler(char  *cmd);
void        ft_print_token(t_token *tokens);
void        print_token(t_token *curr);
void add_node_back(t_token *new, t_token **list);
void	add_redir_back(t_redir *node, t_redir **list);
static void        ft_pustsr(char *s);
char	*get_next_word(char *str, int *j, e_token tok);
int	skip_quotes(char *s, char c);
e_token get_token(char c, char next);
char	*ft_strdup(char	*src);
char	*ft_substr(char *s, unsigned int start, int	len);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
int is_sep(char c);
#endif