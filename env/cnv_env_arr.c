/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnv_env_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:03:46 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/11 10:25:47 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int env_count(t_env **env)
{
	int		count;
	t_env	*tmp;

	tmp = *env;	
	count = 0;
	while(tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*create_env_string(t_env *env)
{
	char *key;
	char *full;

	key = ft_strjoin(env->key, "=");
	if (!key)
		return (NULL);
	full = ft_strjoin(key, env->value);
	free(key);
	return (full);
}

char	**env_list_to_array(t_env **env)
{
	char **arr;
	t_env	*tmp;
	int	i;
	
	arr = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = *env;
	while(i < env_count(env))
	{
		arr[i] = create_env_string(tmp);
		if (!arr[i])
		{
			while (--i >= 0)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
