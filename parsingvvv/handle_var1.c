/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:32:11 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/14 13:08:33 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	handle_exit_status(t_env *env, int *i)
{
	char	*exit_str;
	int		len;

	exit_str = ft_itoa(env->exit_status);
	len = ft_strlen(exit_str);
	free(exit_str);
	*i += 2;
	return (len);
}

int	handle_variable(char *value, t_env *env, char *var_name, int *i)
{
	int		k;
	char	*var_value;

	k = 0;
	(*i)++;
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		var_name[k++] = value[(*i)++];
	var_name[k] = '\0';
	var_value = get_env(var_name, env);
	if (var_value)
		return (ft_strlen(var_value));
	return (0);
}

int	expand_variable_helper(char *value, t_env *env, char *var_name, int t_len)
{
	int		i;

	i = 0;
	t_len = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
			t_len += handle_exit_status(env, &i);
		else if (value[i] == '$' && value[i + 1]
			&& (ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
			t_len += handle_variable(value, env, var_name, &i);
		else
		{
			t_len++;
			i++;
		}
	}
	return (t_len);
}

void	copy_exit_status(t_env *env, char *result, int *j, int *i)
{
	char	*exit_str;
	int		len;

	exit_str = ft_itoa(env->exit_status);
	len = ft_strlen(exit_str);
	ft_memcpy(result + *j, exit_str, len);
	*j += len;
	free(exit_str);
	*i += 2;
}
