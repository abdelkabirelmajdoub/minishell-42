/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:20:52 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/06 12:14:26 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_syn_helper(t_token *cpy_tok)
{
	while (cpy_tok)
	{
		if ((cpy_tok->type == REDIR_APPEND || cpy_tok->type == REDIR_HEREDOC
				|| cpy_tok->type == REDIR_IN || cpy_tok->type == REDIR_OUT)) 
		{
			if (cpy_tok->next == NULL || cpy_tok->next->type != WORD)
			{
				printf("syntax error near unexpected token `newline'\n");
				break ;
			}
		}
		else if (cpy_tok->type == PIPE)
		{
			if (cpy_tok->next == NULL)
				printf("Pipe khasso ykon mraha chi haja \n");
		}
		cpy_tok = cpy_tok->next;
	}
}

void	handle_syn(char *input, t_token *tok)
{
	int		i;
	t_token	*cpy_tok;

	cpy_tok = tok;
	i = 0;
	while (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (input[i] == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		return ;
	}
	handle_syn_helper(cpy_tok);
}
