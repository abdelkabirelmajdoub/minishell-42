/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:56:13 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/10 11:33:19 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
	{
		*env = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (!key)
		node->key = NULL;
	else
		node->key = key;
	if (!value)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

t_env	*node_of_env(char *env_str)
{
	t_env	*new;
	char	*equale_sign;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	equale_sign = ft_strchr(env_str, '=');
	if (equale_sign)
	{
		new->key = ft_strndup(env_str, equale_sign - env_str);
		new->value = ft_strdup(equale_sign + 1);
	}
	else
	{
		new->key = ft_strdup(env_str);
		new->value = NULL;
	}
	if (!new->key || (equale_sign && !new->value))
	{
		free(new->key);
		free(new->value);
		return (free(new), NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*creat_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i])
	{
		new = node_of_env(env[i]);
		if (!new)
			return (free_env(head), NULL);
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	return (head);
}
