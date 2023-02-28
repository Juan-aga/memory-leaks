/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mac.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:22:23 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/28 12:47:58 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"
#include <dlfcn.h>

void	*ft_real_malloc(size_t size)
{
	static void	*(*real_malloc)(size_t) = NULL;

	if (!real_malloc)
		real_malloc = dlsym(RTLD_NEXT, "malloc");
	return (real_malloc(size));
}

void	*ft_real_calloc(size_t size)
{
	static void	*(*real_calloc)(size_t, size_t) = NULL;

	if (!real_calloc)
		real_calloc = dlsym(RTLD_NEXT, "calloc");
	return (real_calloc(size, 1));
}

void	ft_real_free(void *p)
{
	static void	(*real_free)(void*) = NULL;

	if (!real_free)
		real_free = dlsym(RTLD_NEXT, "free");
	real_free(p);
}
