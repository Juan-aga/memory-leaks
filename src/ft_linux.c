/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:49:24 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/28 12:47:46 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"

extern void	*__libc_malloc(size_t size);
extern void	*__libc_calloc(size_t size, size_t t);
extern void	__libc_free(void *to_free);

void	*ft_real_malloc(size_t size)
{
	return (__libc_malloc(size));
}

void	*ft_real_calloc(size_t size)
{
	return (__libc_calloc(size, 1));
}

void	ft_real_free(void *p)
{
	__libc_free(p);
}
