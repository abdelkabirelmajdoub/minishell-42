/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:27:13 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/04 08:23:28 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*fs;
	unsigned char	*ss;
	size_t			i;

	if (n == 0)
	{
		return (0);
	}
	fs = (unsigned char *)s1;
	ss = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (fs[i] != ss[i])
		{
			return (fs[i] - ss[i]);
		}
		i++;
	}
	return (0);
}
