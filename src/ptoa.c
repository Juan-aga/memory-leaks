/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:05:18 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/26 16:40:42 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory_leaks.h"

static char	*ft_fill(char *str, int len, unsigned long long n);
static int	ft_len(unsigned long long n);

char	*ft_ptoa(unsigned long long n)
{
	int		len;
	char	*str;

	len = ft_len(n);
	str = (char *) calloc((len + 1),  sizeof(char));
	if (!str)
		return (NULL);
	return (ft_fill(str, len - 1, n));
}

static int	ft_len(unsigned long long n)
{
	int	i;

	i = 3;

	while (n > 15)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static char	*ft_fill(char *str, int len, unsigned long long n)
{
	while (n > 15)
	{
		if ((n % 16) > 9)
			str[len] = (n % 16) - 10 + 'a';
		else
			str[len] = (n % 16) + '0';
		n /= 16;
		len--;
	}
	if ((n % 16) > 9)
		str[len] = (n % 16) - 10 + 'a';
	else
		str[len] = (n % 16) + '0';
	str[0] = '0';
	str[1] = 'x';
	return (str);
}
