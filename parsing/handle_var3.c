/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:06:51 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/14 13:09:37 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_token(t_token **tokens, t_token *current, t_token *prev)
{
	if (prev)
		prev->next = current->next;
	else
		*tokens = current->next;
	free(current->value);
	free(current);
}

void	clean_empty_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == WORD && current->value
			&& current->value[0] == '\0')
		{
			remove_token(tokens, current, prev);
			current = next;
			continue ;
		}
		prev = current;
		current = next;
	}
}

char	*expand_tilde(const char *value)
{
	char	*home;
	char	*rest;
	char	*result;

	home = getenv("HOME");
	if (!home)
		return (ft_strdup(value));
	if (value[0] == '~' && (value[1] == '\0' || value[1] == '/'))
	{
		rest = ft_strdup(value + 1);
		result = ft_strjoin(home, rest);
		free(rest);
		return (result);
	}
	return (ft_strdup(value));
}

void	expand_word_token(t_token *tok, t_env *env)
{
	char	*expanded;

	if (tok->quote_type != '\'' && ft_strchr(tok->value, '$'))
	{
		expanded = expand_variable(tok->value, env);
		free(tok->value);
		tok->value = expanded;
	}
	if (tok->quote_type == 0 && tok->value[0] == '~')
	{
		expanded = expand_tilde(tok->value);
		free(tok->value);
		tok->value = expanded;
	}
}

void	expend_token(t_token *tokens, t_env *env)
{
	t_token	*cpy_tok;

	cpy_tok = tokens;
	while (cpy_tok)
	{
		if (cpy_tok->type == WORD)
			expand_word_token(cpy_tok, env);
		cpy_tok = cpy_tok->next;
	}
}
