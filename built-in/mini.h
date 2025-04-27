#ifndef MINI_H
#define MINI_H
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;


void	env(t_env *tmp);
void	cd_cmd(char **args);
int		ft_unset(char *var, t_env **my_env);
void	minishell_exit(char **args);
t_env	*creat_env(char **env);
void 	free_args(char **args);
#endif
