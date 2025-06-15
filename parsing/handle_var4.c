/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:08:03 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/14 13:09:40 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_quotes_from_token(t_token *tok)
{
	char	*new_value;
	size_t	len;

	len = ft_strlen(tok->value);
	if (len >= 2 && tok->value[0] == tok->quote_type
		&& tok->value[len - 1] == tok->quote_type)
	{
		new_value = ft_substr(tok->value, 1, len - 2);
		free(tok->value);
		tok->value = new_value;
	}
}

void	handle_quotes(t_token *tokens)
{
	t_token	*tok;

	tok = tokens;
	while (tok)
	{
		if (tok->type == WORD && (tok->quote_type == '\''
				|| tok->quote_type == '"'))
			remove_quotes_from_token(tok);
		tok = tok->next;
	}
}
