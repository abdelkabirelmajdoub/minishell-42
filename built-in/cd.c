/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:55:20 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/24 13:30:59 by ael-majd         ###   ########.fr       */
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

int	run_old(t_env **env)
{
	char	*old_path;

	old_path = get_env("OLDPWD", *env);
	if (!old_path || !*old_path)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (old_path)
		ft_putendl_fd(old_path, 1);
	return (run_cd(old_path));
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
		else if (!ft_strcmp(args[1], "-"))
			flag = run_old(env);
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
