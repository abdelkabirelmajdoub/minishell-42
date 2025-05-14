/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:16:37 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/02 12:41:19 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocatenewstring(void)
{
	char	*a;

	a = malloc(1);
	if (a == NULL)
		return (NULL);
	a[0] = '\0';
	return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			s_len;
	char			*a;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (start >= s_len)
	{
		return (allocatenewstring());
	}
	if (len > s_len - start)
		len = s_len - start;
	a = malloc(len + 1);
	if (a == NULL)
		return (NULL);
	while (i < len)
	{
		a[i] = s[start + i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
