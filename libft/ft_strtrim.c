/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:44:30 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/05 13:16:57 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocation(size_t	t_len)
{
	char	*a;

	a = malloc (t_len + 1);
	if (a == NULL)
		return (NULL);
	return (a);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*a;
	size_t	f_index;
	size_t	l_index;
	size_t	t_len;

	if (!s1 || !set)
		return (NULL);
	f_index = 0;
	while (s1[f_index] != '\0' && ft_strchr(set, s1[f_index]) != NULL)
		f_index++;
	l_index = ft_strlen(s1);
	while (l_index > f_index && ft_strchr(set, s1[l_index - 1]) != NULL)
		l_index--;
	t_len = l_index - f_index;
	a = allocation(t_len);
	if (a == NULL)
		return (NULL);
	l_index = 0;
	while (l_index < t_len)
	{
		a[l_index] = s1[f_index + l_index];
		l_index++;
	}
	a[l_index] = '\0';
	return (a);
}
