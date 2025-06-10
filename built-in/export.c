/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:05:42 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/10 11:37:23 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			return ;
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

void	append_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	char	*val_tmp;

	tmp = *env;
	while (tmp)
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

int	export_assign(t_env **env, t_export_data *data)
{
	if (!is_valid_key(data->key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(data->_arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(data->key);
		free(data->value);
		return (1);
	}
	if (data->append)
		append_env(env, data->key, data->value);
	else
		update_env(env, data->key, data->value);
	free(data->value);
	return (0);
}

int	process_export_arg(t_env **env, char *arg)
{
	t_export_data	data;
	char			*eq;

	data.append = 0;
	eq = ft_strchr(arg, '=');
	data._arg = arg;
	if (eq && eq != arg && *(eq - 1) == '+')
		data.append = 1;
	if (eq)
	{
		if (data.append)
			data.key = ft_strndup(arg, (eq - arg) - 1);
		else
			data.key = ft_strndup(arg, eq - arg);
		data.value = ft_strdup(eq + 1);
	}
	else
	{
		data.key = ft_strdup(arg);
		data.value = NULL;
	}
	return (export_assign(env, &data));
}

int	ft_export(t_env **env, char **args)
{
	int	i;
	int	flag;

	if (!args[1])
		return (print_export(*env));
	i = 1;
	flag = 0;
	while (args[i])
	{
		if (process_export_arg(env, args[i]))
			flag = 1;
		i++;
	}
	return (flag);
}
