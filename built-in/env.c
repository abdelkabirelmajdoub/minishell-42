/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:05:40 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/10 11:39:52 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	empty_env(t_env **env)
{
	char	cwd[1337];
	t_env	*new;

	if (!env)
		return ;
	if (!getcwd(cwd, sizeof(cwd)))
		return ;
	*env = new_env_node("PWD", ft_strdup(cwd));
	if (!*env)
		return ;
	new = new_env_node("SHLVL", ft_strdup("1"));
	if (!new)
		return ;
	(*env)->next = new;
	new->next = new_env_node("_", ft_strdup("/usr/bin/env"));
}

void	hight_lvl(int *lvl)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putnbr_fd(*lvl, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
	*lvl = 1;
}

void	inc_lvl(t_env **env)
{
	t_env	*curr;
	int		lvl;
	char	*new;

	if (!env || !*env)
		return (empty_env(env));
	curr = *env;
	while (curr && ft_strcmp(curr->key, "SHLVL") != 0)
		curr = curr->next;
	if (!curr)
		return (empty_env(env));
	lvl = ft_atoi(curr->value) + 1;
	if (lvl > 1000)
		hight_lvl(&lvl);
	else if (lvl < 0)
		lvl = 0;
	new = ft_itoa(lvl);
	if (!new)
		return ;
	free(curr->value);
	curr->value = new;
}

int	ft_env(t_env **tmp)
{
	t_env	*env;

	env = *tmp;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
