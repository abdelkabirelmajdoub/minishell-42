/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:05:36 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/15 16:05:35 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-')
		i++;
	while(s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
	{
		if (!is_number(args[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(":numeric argument required\n", 2);
			exit(255);
		}
		if (args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		exit_code = ft_atoi(args[1]);
	}
	else 
		ft_putstr_fd("exit\n", 2);
	exit(exit_code);
	return (0);
}
