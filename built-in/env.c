/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:05:40 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/12 12:12:19 by ael-majd         ###   ########.fr       */
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

void	inc_lvl(t_env **env)
{
	t_env	*curr;
	int		lvl;
	char	*new;

	if (!env || !*env)
	{
		empty_env(env);
		return ;
	}
	curr = *env;
	while(curr)
	{
		if (!ft_strcmp(curr->key, "SHLVL"))
		{
			lvl = ft_atoi(curr->value);
			lvl++;
			new = ft_itoa(lvl);
			if (!new)
				return ;
			free(curr->value);
			curr->value = new;
		}
		curr  = curr->next;
	}
}

int	ft_env(t_env **tmp)
{
	t_env *env = *tmp;

	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
