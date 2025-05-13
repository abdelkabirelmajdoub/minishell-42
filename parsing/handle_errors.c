/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:20:52 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/10 11:31:17 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_syn_helper(t_token *cpy_tok)
{
	while (cpy_tok)
	{
		if ((cpy_tok->type == REDIR_APPEND || cpy_tok->type == REDIR_HEREDOC
				|| cpy_tok->type == REDIR_IN || cpy_tok->type == REDIR_OUT)) 
		{
			if (cpy_tok->next == NULL || cpy_tok->next->type != WORD)
				return (ft_putstr_fd("syntax error near unexpected token `newline'\n", 2), 0);
		}
		else if (cpy_tok->type == PIPE)
		{
			if (cpy_tok->next == NULL)
				return (ft_putstr_fd("syntax error near unexpected token \n", 2), 0);
		}
		cpy_tok = cpy_tok->next;
	}
	return (1);
}

int	handle_syn(char *input, t_token *tok)
{
	int		i;
	t_token	*cpy_tok;

	cpy_tok = tok;
	i = 0;
	while (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (input[i] == '|')
	{
		return (printf("syntax error near unexpected token `|'\n"), 0);
		return (0);
	}
	if (handle_syn_helper(cpy_tok) == 0)
		return (0);
	else
		return (1);
	return (1);
}
