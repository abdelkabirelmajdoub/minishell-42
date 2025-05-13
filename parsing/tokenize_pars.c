/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:42:31 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/13 13:45:34 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**args_allocation(void)
{
	char	**args;

	args = malloc (sizeof(char *) * 100);
	if (!args)
		return (NULL);
	return (args);
}

void	pars_helper2(t_token **tok, t_cmd *cmd, int *i)
{
	
	if ((*tok)->type == REDIR_IN)
		cmd->infile = (*tok)->next->value;
	else if ((*tok)->type == REDIR_APPEND)
	{
		cmd->append = (*tok)->next->value;
		cmd->out_file[(*i)++] = (*tok)->next->value;
	}
	else if ((*tok)->type == REDIR_OUT)
		cmd->out_file[(*i)++] = (*tok)->next->value;
	else if ((*tok)->type == REDIR_HEREDOC)
		cmd->limiter = (*tok)->next->value;
}

void	pars_helper(t_token **tok, t_cmd *cmd, char **args, int *argc)
{
	int i;

	i = 0;
	cmd->out_file = malloc(sizeof(char *) * 50);
	while ((*tok) && (*tok)->type != PIPE)
	{
		if (((*tok)->type == REDIR_IN || (*tok)->type == REDIR_OUT
				|| (*tok)->type == REDIR_APPEND 
				|| (*tok)->type == REDIR_HEREDOC)
			&& (*tok)->next)
		{
			pars_helper2(tok, cmd, &i);
			if ((*tok)->type == REDIR_OUT || (*tok)->type == REDIR_APPEND)
			*tok = (*tok)->next->next;
			continue ;
		}

		else if ((*tok)->type == WORD && (*tok)->value 
				&& (*tok)->value[0] != '\0')
			args[(*argc)++] = (*tok)->value;
		*tok = (*tok)->next;
	}
	cmd->out_file[i] = NULL;
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
