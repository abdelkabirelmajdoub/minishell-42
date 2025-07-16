/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pars2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:51:39 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/25 10:39:48 by ael-majd         ###   ########.fr       */
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
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup((*tok)->next->value);
	}
	else if ((*tok)->type == REDIR_APPEND)
	{
		cmd->append = "1";
		cmd->out_file[(*i)++] = ft_strdup((*tok)->next->value);
	}
	else if ((*tok)->type == REDIR_OUT)
	{
		cmd->append = NULL;
		cmd->out_file[(*i)++] = ft_strdup((*tok)->next->value);
	}
	else if ((*tok)->type == REDIR_HEREDOC)
	{
		if (cmd->limiter)
			free(cmd->limiter);
		cmd->limiter = ft_strdup((*tok)->next->value);
	}
}
