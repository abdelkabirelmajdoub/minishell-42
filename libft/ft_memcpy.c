/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:58:02 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/06 10:18:16 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srs;
	unsigned char	*dest;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	srs = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		dest[i] = srs[i];
		i++;
	}
	return (dst);
}
