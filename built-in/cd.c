/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:55:20 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/10 11:42:20 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_cd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	return (0);
}

void	update_pwd(t_env **env)
{
	t_env	*tmp;
	char	cwd[1024];

	tmp = *env;
	while (tmp)
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
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
			found = 1;
			break ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!found)
		env_add_back(env, new_env_node("OLDPWD", oldpwd));
}

void	updated_env(t_env **env, char *oldpwd)
{
	update_oldpwd(env, oldpwd);
	update_pwd(env);
}

int	ft_cd(char **args, t_env **env)
{
	int		flag;
	char	oldpwd[1024];
	char	*home;

	getcwd(oldpwd, sizeof(oldpwd));
	if (args[1])
	{
		if (!args[1][0])
			return (0);
		else if (args[1][0] == '-')
			flag = run_cd(get_env("OLDPWD", *env));
		else
			flag = run_cd(args[1]);
	}
	else
	{
		home = get_env("HOME", *env);
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		flag = run_cd(home);
	}
	if (!flag)
		updated_env(env, oldpwd);
	return (flag);
}
