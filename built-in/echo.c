/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:08:50 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/29 13:29:03 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
void	double_quotes(char *s, t_env **env)
{
	int		i;
	int		start;
	char	*var_name;
	t_env	*tmp;

	i = 1;
	var_name = NULL;
	while (s[i] && s[i] != '\"')
	{
		if (s[i] == '$')
		{
			start = ++i;
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			var_name = ft_substr(s, start, i - start);
			tmp = *env;
			while (tmp)
			{
				if (!ft_strncmp(var_name, tmp->key, ft_strlen(var_name) + 1))
				{
					printf("%s", tmp->value);
					break;
				}
				tmp = tmp->next;
			}
			free(var_name);
		}
		else
			ft_putchar_fd(s[i++], 1);
	}
}

void	single_quotes(char 	*args)
{
	int i;

	i = 0;
	while(args[++i] && i < (int) (ft_strlen(args) - 1))
		ft_putchar_fd(args[i], 1);
}


/// stilll need work on it

void	handle_echo(char **args, t_env **env) 
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
		if (args[i][0] == '\"')
			double_quotes(args[i], env); 
		else if (args[i][0] == '\'')
			single_quotes(args[i]);
		else
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}


