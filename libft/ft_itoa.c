/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:18:31 by yazlaigi          #+#    #+#             */
/*   Updated: 2024/11/01 15:17:29 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numberlen(int number)
{
	size_t	count;

	if (number <= 0)
		count = 1;
	else
		count = 0;
	while (number != 0)
	{
		number /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	number;
	size_t	num_len;
	char	*a;

	number = n;
	num_len = numberlen(number);
	a = malloc (num_len + 1);
	if (a == NULL)
		return (NULL);
	a[num_len] = '\0';
	if (number < 0)
	{
		a[0] = '-';
		number = number * -1;
	}
	if (number == 0)
		a[0] = '0';
	while (number != 0)
	{
		a[--num_len] = (number % 10) + '0';
		number = number / 10;
	}
	return (a);
}
