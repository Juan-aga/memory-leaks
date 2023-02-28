/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ntoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:05:18 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/28 12:48:55 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"

static char	*ft_fill(char *str, int len, unsigned long long n,
				unsigned long long base);
static int	ft_len(unsigned long long n);

char	*ft_ptoa(unsigned long long n)
{
	int		len;
	char	*str;

	len = ft_len(n) + 2;
	str = (char *) calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	return (ft_fill(str, len - 1, n, 16));
}

char	*ft_itoa_unsigned(int n)
{
	int		len;
	char	*str;

	n = (unsigned long long) n;
	len = ft_len(n);
	str = (char *) calloc((len + 5), sizeof(char));
	if (!str)
		return (NULL);
	str = ft_fill(str, len, n, 10);
	str[++len] = '.';
	str[++len] = 'l';
	str[++len] = 'o';
	str[++len] = 'g';
	return (str);
}

static int	ft_len(unsigned long long n)
{
	int	i;

	i = 1;
	while (n > 15)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static char	*ft_fill(char *str, int len, unsigned long long n,
		unsigned long long base)
{
	while (n >= base)
	{
		if ((n % base) > 9)
			str[len] = (n % base) - 10 + 'a';
		else
			str[len] = (n % base) + '0';
		n /= base;
		len--;
	}
	if ((n % base) > 9)
		str[len] = (n % 16) - 10 + 'a';
	else
		str[len] = (n % 16) + '0';
	if (base == 16)
	{
		str[0] = '0';
		str[1] = 'x';
	}
	return (str);
}
