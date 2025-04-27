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


void	env(char **envp);
void 	free_args(char **args);
void	cd_cmd(char **s, char **envp);
#endif
