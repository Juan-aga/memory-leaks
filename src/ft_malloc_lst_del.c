/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_lst_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:28:26 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/28 12:48:27 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"

void	ft_malloc_delone(t_malloc *lst)
{
	if (!lst)
		return ;
	if ((lst)->next && (lst)->prev)
	{
		(lst)->prev->next = (lst)->next;
		(lst)->next->prev = (lst)->prev;
	}
	else if ((lst)->next)
		(lst)->next->prev = NULL;
	else if ((lst)->prev)
		(lst)->prev->next = NULL;
	(lst)->next = NULL;
	(lst)->prev = NULL;
	free((*lst).p);
	free((lst));
}

void	ft_malloc_clear(t_malloc *lst)
{
	t_malloc	*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = (lst)->next;
		ft_malloc_delone(tmp);
	}
}
