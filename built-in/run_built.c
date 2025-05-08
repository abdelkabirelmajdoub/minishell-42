/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:18:34 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/08 13:37:43 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "exit") 
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "unset") 
		|| !ft_strcmp(cmd, "echo") ||!ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export"));
}

int	run_builtin(t_cmd *cmd, t_env **env)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args, env));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd->args, env));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(env));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(cmd->args[1], env));
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(env, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd->args));
	return (1);
}