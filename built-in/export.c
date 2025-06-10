/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:05:42 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/10 10:28:56 by ael-majd         ###   ########.fr       */
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
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while(arr[i])
	{
		j = i + 1;
		while(arr[j])
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

void	update_env(t_env **env, char *key, char *value)
{
	t_env	*cur;
	t_env	*new;
	char	*dup_value;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			if (value)
				cur->value = ft_strdup(value);
			else
				cur->value = NULL;
			free(key);
			return;
		}
		cur = cur->next;
	}
	if (value)
		dup_value = value;
	else
		dup_value = NULL;
	new = new_env_node(key, dup_value);
	env_add_back(env, new);
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
	int		size;
	int		i = 0;
	t_env	**array;

	size = env_size(env);
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

void	append_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	char	*val_tmp;

	tmp = *env;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			val_tmp = tmp->value;
			if (val_tmp)
				tmp->value = ft_strjoin(val_tmp, value);
			else
				tmp->value = ft_strjoin("", value);
			free(key);
			free(val_tmp);
			return ;
		}
		tmp = tmp->next;
	}
	update_env(env, key, value);
}

int	ft_export(t_env **env, char **args)
{
	int		i;
	char	*key;
	char	*value;
	char	*eq;
	int		append;
	int		flag;

	if (!args[1])
		return (print_export(*env));
	i = 1;
	flag = 0;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		append = 0;
		if (eq && eq != args[i] && *(eq - 1) == '+')
		    append = 1;
		if (eq)
		{
			if (append)
   				key = ft_strndup(args[i], (eq - args[i]) - 1);
			else
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
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(key);
			free(value);
			flag = 1;
			i++;
			continue;
		}
		if (append)
			append_env(env, key, value);
		else
			update_env(env, key, value);
		free(value);
		i++;
	}
	return (flag);
}
