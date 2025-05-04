/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:05:40 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/01 14:31:41 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*empty_env(void)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	char	cwd[1337];

	head = NULL;
	current = NULL;
	head = new_env_node("PWD", getcwd(cwd, sizeof(cwd)));
	if (!head)
		return (NULL);
	current = head;
	new = new_env_node("SHLVL", "1");
	if (!new)
		return (NULL);
	current->next = new;
	current = new;
	new = new_env_node("_", "/usr/bin/env");
	if (!new)
		return (NULL);
	current->next = new;
	return (head);
}

t_env	*creat_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	char	*eqaule_sign;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	if (!env || !env[0])
	{
		head = empty_env();
		return (head);
	}
	while(env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		eqaule_sign = ft_strchr(env[i], '=');
		if (eqaule_sign)
		{
			new->key = ft_strndup(env[i], eqaule_sign - env[i]);
			new->value = ft_strdup(eqaule_sign + 1);
		}
		else
		{
			new->key = ft_strdup(env[i]);
			new->value = NULL;
		}
		new->next = NULL;
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	return (head);
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