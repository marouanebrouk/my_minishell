#ifndef MINI2_H
# define MINI2_H

#include "mini.h"
#include <sys/wait.h>

int ft_strcmp(char *s1, char *s2);
int is_builtin(char *cmd);
void	ft_handle_builtins(t_token *list);
void split_args_from_cmd(t_token *token);
char *ft_get_path_cmd(t_token *list,char **envp);
void arahna(t_token *list);
void get_node_args(t_token *list);




#endif