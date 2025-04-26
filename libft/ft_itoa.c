/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:14:58 by ael-majd          #+#    #+#             */
/*   Updated: 2024/11/03 14:04:31 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*s;
	long int	num;

	num = n;
	len = n_len(num);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (num < 0)
	{
		num *= -1;
		s[0] = '-';
	}
	while (--len >= 0 && s[len] != '-')
	{
		s[len] = (num % 10) + '0';
		num /= 10;
	}
	return (s);
}
