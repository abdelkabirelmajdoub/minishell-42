/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:38:06 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/14 13:46:48 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_dollar_sign(char *input, int *i, t_env *env)
{
	if (input[*i + 1] == '?')
		handle_exit_status2(input, i, env);
	else if (input[*i + 1] && (ft_isalpha(input[*i + 1])
			|| input[*i + 1] == '_'))
		handle_variable_expansion(input, i, env);
	else
		env->buffer[env->j++] = input[(*i)++];
}

int	is_word_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|'
		|| c == '<' || c == '>');
}

int	extract_quoted_content(char *input, int *i, char *tmp)
{
	char	quote;
	int		k;

	quote = input[*i];
	(*i)++;
	k = 0;
	while (input[*i] && input[*i] != quote)
		tmp[k++] = input[(*i)++];
	tmp[k] = '\0';
	if (input[*i] == '\0')
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		return (-1);
	}
	if (input[*i] == quote)
		(*i)++;
	return (k);
}

void	handle_single_quote_content(char *tmp, int k, t_env *env)
{
	env->has_single = 1;
	ft_memcpy(env->buffer + env->j, tmp, k);
	env->j += k;
}

void	handle_double_quote_content(char *tmp, t_env *env)
{
	char	*expanded;
	int		len;

	env->has_double = 1;
	expanded = expand_variable(tmp, env);
	if (expanded)
	{
		len = ft_strlen(expanded);
		ft_memcpy(env->buffer + env->j, expanded, len);
		env->j += len;
		free(expanded);
	}
}
