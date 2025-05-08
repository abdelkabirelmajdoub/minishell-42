/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:12:33 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/01 16:29:57 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;

	s_len = ft_strlen(src);
	i = 0;
	if (dstsize == 0 && dst == NULL)
		return (s_len);
	d_len = ft_strlen(dst);
	if (d_len >= dstsize)
	{
		return (dstsize + s_len);
	}
	while (src[i] != '\0' && (d_len + i) < (dstsize - 1))
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (s_len + d_len);
}
