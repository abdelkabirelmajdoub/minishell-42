/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:42:31 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/14 13:52:06 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_redirection(t_token **tok, t_cmd *cmd, int *i)
{
	pars_helper2(tok, cmd, i);
	*tok = (*tok)->next->next;
}

static void	handle_word_token(t_token **tok, char **args, int *argc)
{
	if ((*tok)->value && (*tok)->value[0] == '\0')
		args[(*argc)++] = ft_strdup("");
	else if ((*tok)->value && ((*tok)->value[0] != '\0' 
			|| (*tok)->quote_type != 0))
		args[(*argc)++] = ft_strdup((*tok)->value);
}

void	pars_helper(t_token **tok, t_cmd *cmd, char **args, int *argc)
{
	int	i;

	i = 0;
	cmd->out_file = malloc(sizeof(char *) * 50);
	if (!cmd->out_file)
		return ;
	while ((*tok) && (*tok)->type != PIPE)
	{
		if (((*tok)->type == REDIR_IN || (*tok)->type == REDIR_OUT
				|| (*tok)->type == REDIR_APPEND 
				|| (*tok)->type == REDIR_HEREDOC) && (*tok)->next)
		{
			handle_redirection(tok, cmd, &i);
			continue ;
		}
		else if ((*tok)->type == WORD)
			handle_word_token(tok, args, argc);
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
