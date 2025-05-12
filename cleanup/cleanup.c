/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:04:45 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/12 12:24:21 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_args(char **args)
{
	int i;	

	if (!args || !*args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	free_tokens(t_token *tok)
{
	t_token *tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while(cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp->append);
		free(tmp->limiter);
		free(tmp->out_file);
		free(tmp->infile);
		if (tmp->args)
			free_args(tmp->args);
		free(tmp);
	}
}
