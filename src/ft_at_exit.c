/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_at_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:15:41 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/28 12:47:23 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"

static void	ft_free_all(t_mem_check *mem_check, t_mem_report *mem_report);
static void	ft_exit_report(t_mem_check *mem_check, t_mem_report *mem_report);

void	ft_exit(void)
{
	ft_alloc(0, NULL, 0, NULL, NULL, 3);
}

void	*ft_check_at_exit(t_mem_check *mem_check, int *fill_check_memory)
{
	t_mem_report	*mem_report;

	ft_count_free(mem_check);
	ft_count_alloc(mem_check->alloc, mem_check->alloc);
	ft_count_alloc(mem_check->free, mem_check->alloc);
	mem_report = calloc(sizeof(t_mem_report), 1);
	ft_exit_report(mem_check, mem_report);
	ft_report(mem_check, mem_report);
	ft_free_all(mem_check, mem_report);
	*fill_check_memory = 1;
	return (NULL);
}

static void	ft_free_all(t_mem_check *mem_check, t_mem_report *mem_report)
{
	ft_malloc_clear(mem_check->alloc);
	ft_malloc_clear(mem_check->free);
	free(mem_report);
}

static void	ft_exit_report(t_mem_check *mem_check, t_mem_report *report)
{
	t_malloc	*tmp;

	report->leaks = 0;
	report->double_free = 0;
	report->not_allocated = 0;
	tmp = mem_check->alloc;
	while (tmp)
	{
		if (tmp->num_free < tmp->num_alloc)
			report->leaks += 1;
		else if (tmp->num_free > tmp->num_alloc)
			report->double_free += 1;
		tmp = tmp->next;
	}
	tmp = mem_check->free;
	while (tmp)
	{
		if (tmp->num_alloc == 0)
			report->not_allocated += 1;
		tmp = tmp->next;
	}
}
