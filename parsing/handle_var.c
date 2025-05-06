/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:32:11 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/06 10:28:18 by yazlaigi         ###   ########.fr       */
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

char	*expand_variable(char *value, t_env *env)
{
	char	*var_value;
	char	*var_name;
	char	*output;

	var_name = value + 1;
	var_value = get_env (var_name, env);
	if (!var_value)
		return (NULL);
	output = ft_strdup(var_value);
	return (output);
}

void	*expend_token(t_token *tokens, t_env *env)
{
	t_token	*cpy_tok;
	char	*expanded;

	cpy_tok = tokens;
	while (cpy_tok)
	{
		if (cpy_tok->type == WORD && cpy_tok->value[0] == '$')
		{
			expanded = expand_variable(cpy_tok->value, env);
			free(cpy_tok->value);
			cpy_tok->value = expanded; 
		}
		cpy_tok = cpy_tok->next;
	}
}
