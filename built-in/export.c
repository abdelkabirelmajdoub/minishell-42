/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:53:52 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/01 14:40:01 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	is_valid_key(char *key)
{
	int	i = 0;

	if (!key || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
void	sort_env_array(t_env **arr)
{
	int		i, j;
	t_env	*tmp;

	for (i = 0; arr[i]; i++)
	{
		for (j = i + 1; arr[j]; j++)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}
void	add_env_back(t_env **env, t_env *new)
{
	t_env *cur = *env;

	if (!cur)
	{
		*env = new;
		return;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	update_env(t_env **env, char *key, char *value)
{
	t_env *cur = *env;

	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = value ? ft_strdup(value) : NULL;
			free(key);
			return;
		}
		cur = cur->next;
	}
	t_env *new = new_env_node(key, value ? ft_strdup(value) : NULL);
	add_env_back(env, new);
}
int	env_size(t_env *env)
{
	int count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return count;
}

t_env	**env_to_array(t_env *env)
{
	int		size = env_size(env);
	int		i = 0;
	t_env	**array = malloc(sizeof(t_env *) * (size + 1));

	if (!array)
		return (NULL);
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}




int	print_export(t_env *env)
{
	t_env	**arr = env_to_array(env);
	int		i;

	sort_env_array(arr); // sort by key
	i = 0;
	while (arr[i])
	{
		if (arr[i]->value)
			printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		else
			printf("declare -x %s\n", arr[i]->key);
		i++;
	}
	// free_args(arr);
	return (0);
}


int	ft_export(t_env **env, char **args)
{
	int		i = 1;
	char	*key;
	char	*value;
	char	*eq;

	if (!args[1]) // No arguments: print all in sorted order
		return (print_export(*env));

	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			key = ft_strndup(args[i], eq - args[i]);
			value = ft_strdup(eq + 1);
		}
		else
		{
			key = ft_strdup(args[i]);
			value = NULL;
		}
		if (!is_valid_key(key))
		{
			printf("export: `%s': not a valid identifier\n", args[i]);
			free(key);
			free(value);
			i++;
			continue;
		}
		update_env(env, key, value); // add or update variable
		i++;
	}
	return (0);
}

