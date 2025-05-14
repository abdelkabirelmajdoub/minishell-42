/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:36:04 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/11 07:55:49 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	while (i > 0)
	{
		if (s[i - 1] == (char)c)
		{
			return ((char *)&s[i - 1]);
		}
		i--;
	}
	return (NULL);
}
