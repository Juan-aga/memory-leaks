/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42memory_leaks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:43:02 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/26 03:11:29 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory_leaks.h"
#include <sys/wait.h>

static void	*ft_malloc_hook(t_mem_check *mem_check, int *fill_check_memory, t_mem_data data);
static void	ft_init_check(t_mem_check **mem_check, int *fill_check_memory);
static void	*ft_free_hook(t_mem_check *mem_check, int *fill_check_memory, t_mem_data data);
static void	ft_check_at_exit(t_mem_check *mem_check, int *fill_check_memory);

void	ft_exit(void)
{
	ft_alloc(0, NULL, 0, NULL, NULL, 2);
}

void	*ft_alloc(size_t size, const char *file, int line, const char *func, void *to_free, int control)
{
	static t_mem_check	*mem_check = NULL; //= (t_mem_check){NULL, NULL, };
	static int			fill_check_memory = 1;
	t_mem_data			data;

	if (fill_check_memory)
	{
		data.size = size;
		data.file = file;
		data.line = line;
		data.func = func;
		data.alloc = to_free;
		ft_init_check(&mem_check, &fill_check_memory);
		fill_check_memory = 0;
		if (control == 0)
			return (ft_malloc_hook(&(*mem_check), &fill_check_memory, data));
		if (control == 1)
			return (ft_free_hook(&(*mem_check), &fill_check_memory, data));
		if (control == 2)
			ft_check_at_exit(&(*mem_check), &fill_check_memory);
	}
	else
	{
		if (control == 0)
			return (__libc_malloc(size));
		if (control == 1)
			return (__libc_free(to_free));
	}
}

static void	ft_init_check(t_mem_check **mem_check, int *fill_check_memory)
{
	static struct rlimit	max_proc = {0, 0};
	pid_t					pid;
	static pid_t			*proc;
	int						i;

	i = 0;
	proc = calloc(100, sizeof(pid_t));
	pid = getpid();
	while (proc[i])
	{
		if (proc[i] == pid)
			break ;
		i++;
	}
	if (!proc[i])
		proc[i] = pid;
	if (!max_proc.rlim_cur)
	{
		getrlimit(RLIMIT_NPROC, &max_proc);
		atexit(ft_memory_leaks);
	}
	if (!*mem_check)//->alloc[pid])
	{
		write(1, "1\n", 2);
		*fill_check_memory = 0;
		mem_check = calloc(sizeof(t_mem_check *), 1);
//		if (!mem_check)
//			return ;
		*mem_check->alloc[i] = calloc(sizeof(t_malloc *), 1);
		if (!(*mem_check)->alloc)
			return ;
		(*mem_check)->max_proc = &max_proc;
		*fill_check_memory = 1;
	}
	(*mem_check)->pid = proc[i];
	printf("\n pid: %i\n", (*mem_check)->pid);
}

static void	*ft_malloc_hook(t_mem_check *mem_check, int *fill_check_memory, t_mem_data data)
{
	void		*result;
	static int	count = 0;
//	t_malloc	*m;

	data.alloc = __libc_malloc(data.size);
	if (count == 0)
		mem_check->alloc[mem_check->pid] = ft_malloc_new(data);
	else
		ft_malloc_add_back(&mem_check->alloc[mem_check->pid], ft_malloc_new(data));
//	m = mem_check->alloc[mem_check->pid];
//	result = malloc(mem_check->alloc[mem_check->pid]->size);
//	mem_check->alloc[mem_check->pid]->p = ft_ptoa((unsigned long long) result);
	mem_check->alloc[mem_check->pid]->alloc = result;
	*fill_check_memory = 1;
	count++;
	printf("\t en malloc pid es: %i\n", mem_check->pid);
//	printf("puntero %p allocado en %s %s:%i process: %i\n en char es [%s]\n", result, mem_check->alloc[mem_check->pid]->file, mem_check->alloc[mem_check->pid]->func, mem_check->alloc[mem_check->pid]->line, mem_check->pid, mem_check->alloc[mem_check->pid]->p);
	return (result);
}

static void	*ft_free_hook(t_mem_check *mem_check, int *fill_check_memory, t_mem_data data)
{
	free(data.alloc);
	*fill_check_memory = 1;
	return (NULL);
}

static void	ft_check_at_exit(t_mem_check *mem_check, int *fill_check_memory)
{
	int			num_malloc;
	int			num_free;
	t_malloc	*tmp;
	
//	waitpid((*mem_check)->pid, &num_free, 0);
	tmp = mem_check->alloc[mem_check->pid];
	printf("\texit process: %i\n", mem_check->pid);
	while (tmp)
	{
		printf("\t[%s] memory allocated at: %s %s:%i\n", tmp->p, tmp->file, tmp->func, tmp->line);
		tmp = tmp->next;
	}
	*fill_check_memory = 1;
//	exit(0);
}
