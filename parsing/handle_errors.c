/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:20:52 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/18 12:55:07 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_syn_helper(t_token *cpy_tok, t_env **env)
{
	while (cpy_tok)
	{
		if ((cpy_tok->type == REDIR_APPEND || cpy_tok->type == REDIR_HEREDOC 
				|| cpy_tok->type == REDIR_IN || cpy_tok->type == REDIR_OUT))
		{
			if (cpy_tok->next == NULL || cpy_tok->next->type != WORD)
			{
				ft_putstr_fd(SYNTHAX_RED, 2);
				(*env)->exit_status = 258;
				return (0);
			}
		}
		else if (cpy_tok->type == PIPE)
		{
			if (cpy_tok->next == NULL)
				return ((*env)->exit_status = 258, 
					ft_putstr_fd(SYNTHAX_PIPE, 2), 0);
			if (cpy_tok->next->type == PIPE)
				return ((*env)->exit_status = 258, 
					ft_putstr_fd(SYNTHAX_PIPE, 2), 0);
		}
		cpy_tok = cpy_tok->next;
	}
	return (1);
}

int	handle_syn(char *input, t_token *tok, t_env **env)
{
	int		i;
	t_token	*cpy_tok;

	cpy_tok = tok;
	i = 0;
	while (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (input[i] == '|')
	{
		(*env)->exit_status = 258;
		return (ft_putstr_fd(SYNTHAX_PIPE, 2), 0);
	}
	if (handle_syn_helper(cpy_tok, env) == 0)
		return (0);
	return (1);
}
