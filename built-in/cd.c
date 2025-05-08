#include "../include/minishell.h"

void	env_add_back(t_env **env, t_env *new_node)
{
	t_env *tmp;

	tmp = *env;
	if (!tmp)
	{
		*env = new_node;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}


int run_cd(char *path)
{
	if (chdir(path) == -1)
		return (perror("cd"), 0);
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
void	update_oldpwd(t_env **env, char *oldpwd)
{
	t_env	*tmp;
	int		found;

	found = 0;
	tmp = *env;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
			found = 1;
			break;
		}
		if (!tmp->next)
			break;
		tmp = tmp->next;
	}
	if (!found)
		env_add_back(env, new_env_node("OLDPWD", oldpwd));
}

int	ft_cd(char **args, t_env **env)
{
	int		flag;
	char	oldpwd[1024];

	getcwd(oldpwd, sizeof(oldpwd));
	if (args[1] && args[1][0] == '~')
		flag = run_cd(getenv("HOME"));
	else if (args[1])
		flag = run_cd(args[1]);
	else
		flag = run_cd(getenv("HOME"));
	if (flag)
	{
		update_oldpwd(env, oldpwd);
		update_pwd(env);
	}
	return (0);
}