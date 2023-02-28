/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:03:45 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/28 12:48:14 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"

t_malloc	*ft_malloc_new(t_mem_data data)
{
	t_malloc	*lst;

	lst = (t_malloc *) calloc(1, sizeof(t_malloc));
	if (!lst)
		return (NULL);
	lst->size = data.size;
	lst->line = data.line;
	lst->file = data.file;
	lst->func = data.func;
	lst->p = ft_ptoa((unsigned long long) data.alloc);
	lst->alloc = data.alloc;
	lst->num_free = 0;
	lst->num_alloc = 0;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

t_malloc	*ft_malloc_last(t_malloc *lst)
{
	t_malloc	*tmp;

	tmp = lst;
	if (lst)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}

void	ft_malloc_add_back(t_malloc **lst, t_malloc *new)
{
	t_malloc	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_malloc_last(*lst);
	last->next = new;
	new->prev = last;
}

int	ft_malloc_size(t_malloc *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
