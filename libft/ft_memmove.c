/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:26:51 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/06 10:22:21 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*srs;
	unsigned char	*dest;
	size_t			i;

	srs = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	if (dest < srs)
	{
		while (i < n)
		{
			dest[i] = srs[i];
			i++;
		}
	}
	else if (dest > srs)
	{
		while (n > 0)
		{
			dest[n - 1] = srs[n - 1];
			n--;
		}
	}
	return (dst);
}
