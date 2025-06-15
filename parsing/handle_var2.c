/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:59:52 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/14 13:09:30 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	extract_var_name(char *value, char *var_name, int *i)
{
	int	k;

	k = 0;
	(*i)++;
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		var_name[k++] = value[(*i)++];
	var_name[k] = '\0';
	return (k);
}

void	copy_var_value(char *var_value, char *result, int *j)
{
	int	len;

	len = ft_strlen(var_value);
	ft_memcpy(result + *j, var_value, len);
	*j += len;
}

char	*allocate_result(char *value, t_env *env)
{
	char	var_name[256];
	int		total_len;

	total_len = expand_variable_helper(value, env, var_name, 0);
	return (malloc(total_len + 1));
}

void	process_expansion(char *value, t_env *env, char *result)
{
	char	var_name[256];
	char	*var_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
			copy_exit_status(env, result, &j, &i);
		else if (value[i] == '$' && value[i + 1]
			&& (ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
		{
			extract_var_name(value, var_name, &i);
			var_value = get_env(var_name, env);
			if (var_value)
				copy_var_value(var_value, result, &j);
		}
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
}

char	*expand_variable(char *value, t_env *env)
{
	char	*result;

	result = allocate_result(value, env);
	if (!result)
		return (NULL);
	process_expansion(value, env, result);
	return (result);
}
