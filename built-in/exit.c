/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:05:36 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/10 11:38:52 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_number(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if ((s[0] == '-' || s[0] == '+') && s[1] == '\0')
		return (0);
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	first_arg(char *trimmed, char **args)
{
	if (!is_number(trimmed) || trimmed[0] == '\0')
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free(trimmed);
		exit(255);
	}
}

int	ft_exit(char **args, t_env **env)
{
	int		exit_code;
	char	*trimmed;

	exit_code = (*env)->exit_status;
	if (args[1])
	{
		trimmed = ft_strtrim(args[1], " ");
		first_arg(trimmed, args);
		if (args[2])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: too many arguments\n", 2);
			free(trimmed);
			return (1);
		}
		exit_code = ft_atoi(trimmed);
		free(trimmed);
	}
	ft_putstr_fd("exit\n", 2);
	exit(exit_code);
	return (0);
}
