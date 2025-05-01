#include "../include/minishell.h"


int run_cd(char *path)
{
	if (chdir(path) == -1)
		perror("cd");
	return (1);
}

void free_args(char **args)
{
	int i;	

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
int	ft_cd(char **args)
{
	if (args[1] && args[1][0] == '~')
		run_cd(getenv("HOME"));
	else if (args[1])
		run_cd(args[1]);
	else
		run_cd(getenv("HOME"));
	return (0);
}