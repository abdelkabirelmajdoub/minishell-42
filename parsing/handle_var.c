/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:32:11 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/05 11:52:55 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_variables(t_token    *tok)
{
	t_token	*cpy_token;

	cpy_token = tok;
	while (cpy_token)
	{
		if (cpy_token->type == WORD && cpy_token->value[0] == '$')
			return (cpy_token->value);
		cpy_token = cpy_token->next;
	}
	return (NULL);
}

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