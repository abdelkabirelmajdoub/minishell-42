/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:21:15 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/04 13:08:00 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (0);
	if (s[0] != c && s[0] != '\0')
		j = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j += 1;
		i++;
	}
	return (j);
}

static int	ft_word_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	memmoryfree(char **a, int i)
{
	while (i > 0)
		free(a[--i]);
	free (a);
}

static char	*allocation(int size, const char *s)
{
	char	*a;
	int		i;

	a = malloc(size);
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < size - 1 && s[i] != '\0')
	{
		a[i] = s[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	**ft_split(char const *s, char c)
{
	int		words_num;
	int		i;
	char	**a;

	if (!s)
		return (NULL);
	words_num = count_words(s, c);
	a = (char **)malloc((words_num + 1) * sizeof(char *));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < words_num)
	{
		while (*s == c && *s != '\0')
			s++;
		a[i] = allocation (ft_word_len(s, c) + 1, s);
		if (a[i++] == NULL)
		{
			memmoryfree(a, --i);
			return (NULL);
		}
		s = s + ft_word_len(s, c);
	}
	a[i] = NULL;
	return (a);
}
