/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pars2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:51:39 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/23 17:51:34 by ael-majd         ###   ########.fr       */
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
		cmd->infile = ft_strdup((*tok)->next->value);
	else if ((*tok)->type == REDIR_APPEND)
	{
		cmd->append = "1";
		cmd->out_file[(*i)++] = ft_strdup((*tok)->next->value);
	}
	else if ((*tok)->type == REDIR_OUT)
		cmd->out_file[(*i)++] = ft_strdup((*tok)->next->value);
	else if ((*tok)->type == REDIR_HEREDOC)
		cmd->limiter = ft_strdup((*tok)->next->value);
}
