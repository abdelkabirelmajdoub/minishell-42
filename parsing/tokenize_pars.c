/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:42:31 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/30 12:36:11 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*pars_int(void)
{
	t_cmd	*cmd;

	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->out_file = NULL;
	cmd->append = NULL;
	cmd->next = NULL;
	return (cmd);
}

char	**args_allocation(void)
{
	char	**args;

	args = malloc (sizeof(char *) * 100);
	if (!args)
		return (NULL);
	return (args);
}

void	pars_helper(t_token **tok, t_cmd *cmd, char **args, int *argc)
{
	while ((*tok) && (*tok)->type != PIPE)
	{
		if ((*tok)->type == REDIR_IN && (*tok)->next)
		{
			cmd->infile = (*tok)->next->value;
			*tok = (*tok)->next->next;
			continue ;
		}
		else if ((*tok)->type == REDIR_OUT && (*tok)->next)
		{
			cmd->out_file = (*tok)->next->value;
			*tok = (*tok)->next->next;
			continue ;
		}
		else if ((*tok)->type == REDIR_APPEND && (*tok)->next)
		{
			cmd->append = (*tok)->next->value;
			*tok = (*tok)->next->next;
			continue ;
		}
		else if ((*tok)->type == WORD)
			args[(*argc)++] = (*tok)->value;
		*tok = (*tok)->next;
	}
}

int	init_cmd(t_cmd **cmd, char ***args)
{
	*cmd = pars_int();
	*args = args_allocation();
	if (!*cmd || !*args)
		return (0);
	return (1);
}

t_cmd	*pars_token(t_token	*tok)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*cmd;
	char	**args;
	int		argc;

	head = NULL;
	current = NULL;
	while (tok)
	{
		argc = 0;
		if (!init_cmd(&cmd, &args))
			return (NULL);
		pars_helper(&tok, cmd, args, &argc);
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
