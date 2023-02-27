/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_report.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:44:38 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/27 14:35:27 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory_leaks.h"

static void	ft_leaks(t_malloc *tmp);
static void	ft_double_free(t_mem_check *mem_check);
static void	ft_not_allocated(t_malloc *tmp);

void	ft_report(t_mem_check *mem_check, t_mem_report *mem_report)
{
	pid_t		pid;
	t_malloc	*tmp;

	pid = getpid();
	printf("\n\tMemory leaks report for process: %i\n\n", pid);
	printf("\tProcess: %i\tmemory leaks:\t\t%i\n", pid, mem_report->leaks);
	printf("\tProcess: %i\tdouble free:\t\t%i\n", pid, mem_report->double_free);
	printf("\tProcess: %i\tmemory not allocated:\t%i\n", pid,
		mem_report->not_allocated);
	tmp = mem_check->alloc;
	if (mem_report->leaks)
		ft_leaks(tmp);
	if (mem_report->double_free)
		ft_double_free(mem_check);
	tmp = mem_check->free;
	if (mem_report->not_allocated)
		ft_not_allocated(tmp);
}

static void	ft_leaks(t_malloc *tmp)
{
	printf("\n\tLeaks report:\n");
	while (tmp)
	{
		if (tmp->num_free < tmp->num_alloc)
			printf("\tmemory: [%s] allocated at %s %s:%i not freed.\n",
				tmp->p, tmp->file, tmp->func, tmp->line);
		tmp = tmp->next;
	}
}

static void	ft_double_free(t_mem_check *mem_check)
{
	t_malloc	*tmp;
	t_malloc	*free;

	tmp = mem_check->alloc;
	printf("\n\tDouble free report:\n");
	while (tmp)
	{
		free = mem_check->free;
		if (tmp->num_free > tmp->num_alloc)
		{
			printf("\tmemory: [%s] allocated at %s %s:%i freed at:\t", tmp->p,
				tmp->file, tmp->func, tmp->line);
			while (free)
			{
				if (!ft_strcmp(tmp->p, free->p))
					printf("\t\t%s %s:%i\n", free->file, free->func,
						free->line);
				free = free->next;
			}
		}
		tmp = tmp->next;
	}
}

static void	ft_not_allocated(t_malloc *tmp)
{
	printf("\n\tMemory not allocated report:\n");
	while (tmp)
	{
		if (!tmp->num_alloc)
			printf("\t memory: [%s] freed at %s %s:%i was not allocated.\n",
				tmp->p, tmp->file, tmp->func, tmp->line);
		tmp = tmp->next;
	}
}
