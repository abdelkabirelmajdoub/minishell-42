/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:20:52 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/04 10:48:45 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_syn(char *input, t_token *tok)
{
	int	i;
	int	end;
	t_token	*cpy_tok;
	
	cpy_tok = tok;
	i = 0;
	while (input[i])
		i++;
	end = i - 1;
	i = 0;
	while (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (input[i] == '|' || input[end] == '|')
	{
		printf("Ops ! Pipe can't be the first or th end of the input\n");
		exit(0);
	}
	while (cpy_tok)
	{
		if ((cpy_tok->type == REDIR_APPEND || cpy_tok->type == REDIR_HEREDOC
			|| cpy_tok->type == REDIR_IN || cpy_tok->type == REDIR_OUT)) 
		{
			if ( cpy_tok->next == NULL || cpy_tok->next->type != WORD )
			{
				printf("special operators must be followed by a word!\n");
				exit(0);
			}
		}
		cpy_tok = cpy_tok->next;
	}
	return (1);
}
