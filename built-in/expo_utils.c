/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:19:36 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/10 11:38:16 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sort_env_array(t_env **arr)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_export(t_env *env)
{
	t_env	**arr;
	int		i;

	arr = env_to_array(env);
	sort_env_array(arr);
	i = 0;
	while (arr[i])
	{
		if (arr[i]->value)
			printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		else
			printf("declare -x %s\n", arr[i]->key);
		i++;
	}
	free(arr);
	return (0);
}

t_env	**env_to_array(t_env *env)
{
	int		size;
	int		i;
	t_env	**array;

	i = 0;
	size = env_count(&env);
	array = malloc(sizeof(t_env *) * (size + 1));
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

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
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
