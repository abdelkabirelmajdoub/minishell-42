/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:34:39 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/22 12:32:02 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j + 1);
		if (ft_strncmp(sub, name, 4) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	*path_part;
	char	*exec;
	char	**secure_paths;
	int		i;

	secure_paths = ft_split(my_getenv("PATH", env), ':');
	if (!secure_paths || !*secure_paths)
		return (cmd);
	i = 0;
	while (secure_paths[i])
	{
		path_part = ft_strjoin(secure_paths[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (free_args(secure_paths), exec);
		free(exec);
		i++;
	}
	free_args(secure_paths);
	return (cmd);
}

int	my_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	count_word(const char *str)
{
	int	i;
	int	in_word;
	int	count;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (!my_isspace(str[i]) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (my_isspace(str[i]))
			in_word = 0;
		i++;
	}
	return (count);
}

char	**advance_split(char *s)
{
	char	**args;
	int		i;
	int		start;
	int		end;
	int		j;

	if (!s)
		return (NULL);
	args = malloc(sizeof(char *) * (count_word(s) + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && my_isspace(s[i]))
			i++;
		start = i;
		while (s[i] && !my_isspace(s[i]))
			i++;
		end = i;
		if (end > start)
			args[j++] = ft_substr(s, start, end - start);
	}
	return (args[j] = NULL, args);
}
