/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:08:50 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/08 10:41:50 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_n_option(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while(str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
// void	double_quotes(char *s, t_env **env)
// {
// 	int	i;
// 	int start;
// 	char *_var;

// 	i = 0;
// 	while(s[i])
// 	{
// 		if (s[i++] == '$')
// 		{
// 			start = i;
// 			while(s[i] && s[i] != ' ')
// 				i++;
// 			_var = ft_substr(s, start, i - start);			
// 		}
// 		else
// 			ft_putchar_fd(s[i], 1);
// 		i++;
// 	}
// 	while(*env)
// 	{
// 		if (!ft_strncmp(_var, (*env)->key, ft_strlen(_var)))
// 		{
// 			printf("%s", (*env)->value);
// 			break;
// 		}
// 		*env = (*env)->next;
// 	}
// }
// stilll need work on it

int	ft_echo(char **args, t_env **env) 
{
	int	i;
	int newline;

	i = 1;
	while (args[i] && is_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while(args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	(void) env;
	return (0);
}


