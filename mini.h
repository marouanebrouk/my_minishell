    #ifndef MINI_H
# define MINI_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define SEP " \t\n"
# define SYNTAX_ERR		"bash: syntax error near unexpected token\n "

typedef     enum  s_token
{
    PIPE, //0
    IN,//1
    OUT,//2
    APPEND,//3
    HERDOK,//4
    NOT, //5
    END//6
}e_token;

typedef struct      s_redirection
{
    e_token     type;
    int     fd;
    char        *file;
    char        *data;
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

char	*ft_strjoin(char	*s1, char *s2);
char	**ft_split(char *str, char charset);
char	*ft_strchr(const char	*s, int c);
int     ft_strlen(char *str);

int     is_set(char c, char *set);
char        *ft_remove_space(char   *s1, char *set);
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
char	*ft_strjoin(char	*s1, char *s2);
int is_sep(char c);






// EXECUTION



typedef struct s_pipelist
{
    char *value;
    char **arguments;
    struct s_pipelist *next;
} t_pipelist;

int ft_strcmp(char *s1, char *s2);
int is_builtin(char *cmd);
void	ft_handle_builtins(t_token *list,char **envp);
void split_args_from_cmd(t_token *token);
char *ft_get_path_cmd(char *value, char **envp);
void arahna(t_token *list);
void get_node_args(t_token *list);


#endif
