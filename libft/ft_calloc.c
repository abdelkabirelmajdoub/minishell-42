/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:21:53 by ael-majd          #+#    #+#             */
/*   Updated: 2024/11/12 09:33:50 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*call;
	size_t	n;

	n = size * count;
	if (size && count > n / size)
		return (NULL);
	call = malloc(n);
	if (!call)
		return (NULL);
	else
		ft_bzero(call, n);
	return (call);
}
