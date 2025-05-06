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

void	update_pwd(t_env **env)
{
	t_env	*tmp;
	char	cwd[1024];

	tmp = *env;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			getcwd(cwd, sizeof(cwd));
			tmp->value = ft_strdup(cwd);
		}
		tmp = tmp->next;
	}
}

int	ft_cd(char **args, t_env **env)
{
	if (args[1] && args[1][0] == '~')
		run_cd(getenv("HOME"));
	else if (args[1])
		run_cd(args[1]);
	else
		run_cd(getenv("HOME"));
	update_pwd(env);
	return (0);
}