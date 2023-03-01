/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_report.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:44:38 by juan-aga          #+#    #+#             */
/*   Updated: 2023/03/01 09:44:11 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"
#include <fcntl.h>

static void	ft_leaks(t_malloc *tmp);
static void	ft_double_free(t_mem_check *mem_check);
static void	ft_not_allocated(t_malloc *tmp);
static void	ft_report_file(pid_t pid);

void	ft_report(t_mem_check *mem_check, t_mem_report *mem_report)
{
	pid_t		pid;
	t_malloc	*tmp;

	pid = getpid();
	if (LOG)
		ft_report_file(pid);
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
	printf("\n");
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

static void	ft_report_file(pid_t pid)
{
	char	*file;
	int		fd;

	file = ft_itoa_unsigned(pid);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(file);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	free(file);
}
