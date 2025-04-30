/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:42:31 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/30 09:45:55 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*pars_token(token	*tok)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;
	t_cmd	*cmd;
	char	**args;
	int		argc;

	while (tok)
	{
		cmd = malloc (sizeof(t_cmd));
		if (!cmd)
			return (NULL);
        cmd->args = NULL;
		cmd->infile = NULL;
		cmd->out_file = NULL;
		cmd->append = NULL;
		cmd->next = NULL;
		args = malloc (sizeof(char *) * 100);
		argc = 0;
		while (tok && tok->type != PIPE)
		{
			if (tok->type == REDIR_IN && tok->next)
			{
				cmd->infile = tok->next->value;
				tok = tok->next->next;
				continue;
			}
			else if (tok->type == REDIR_OUT && tok->next)
			{
				cmd->out_file = tok->next->value;
				tok = tok->next->next;
				continue;
			}
			else if (tok->type == REDIR_APPEND && tok->next)
			{
				cmd->append = tok->next->value;
				tok = tok->next->next;
				continue;
			}
			else if (tok->type == WORD)
				args[argc++] = tok->value;
			tok = tok->next;
		}
		args[argc] = NULL;
		cmd->args = args;
		if (!head)
			head = cmd;
		else
			current->next = cmd;
		current = cmd;
		if (tok && tok->type == PIPE)
			tok = tok->next;
	}
	return (head);
}
