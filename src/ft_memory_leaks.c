/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_leaks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:43:02 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/28 12:48:40 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"

static void	*ft_malloc_hook(t_mem_check *mem_check, int *fill_check_memory,
				t_mem_data data, int control);
static void	ft_init_check(t_mem_check *mem_check, int *fill_check_memory);
static void	*ft_free_hook(t_mem_check *mem_check, int *fill_check_memory,
				t_mem_data data);

void	*ft_alloc(size_t size, const char *file, int line, const char *func,
				void *to_free, int control)
{
	static t_mem_check	mem_check = (t_mem_check){NULL, NULL, NULL};
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
		if (control <= 1)
			return (ft_malloc_hook(&mem_check, &fill_check_memory, data,
					control));
		if (control == 2)
			return (ft_free_hook(&mem_check, &fill_check_memory, data));
		if (control == 3)
			ft_check_at_exit(&mem_check, &fill_check_memory);
	}
	else
	{
		if (control == 0)
			return (ft_real_malloc(size));
		if (control == 1)
			return (ft_real_calloc(size));
		if (control == 2)
			ft_real_free(to_free);
	}
	return (NULL);
}

static void	ft_init_check(t_mem_check *mem_check, int *fill_check_memory)
{
	static struct rlimit	max_proc = {0, 0};

	if (!max_proc.rlim_cur)
	{
		getrlimit(RLIMIT_NPROC, &max_proc);
		atexit(ft_memory_leaks);
	}
	if (!mem_check->alloc)
	{
		mem_check->max_proc = &max_proc;
		*fill_check_memory = 1;
	}
}

static void	*ft_malloc_hook(t_mem_check *mem_check, int *fill_check_memory,
				t_mem_data data, int control)
{
	if (!control)
		data.alloc = malloc(data.size);
	else
		data.alloc = calloc(data.size, 1);
	ft_malloc_add_back(&(mem_check)->alloc, ft_malloc_new(data));
	*fill_check_memory = 1;
	return (data.alloc);
}

static void	*ft_free_hook(t_mem_check *mem_check, int *fill_check_memory,
				t_mem_data data)
{
	ft_malloc_add_back(&(mem_check)->free, ft_malloc_new(data));
	free(data.alloc);
	*fill_check_memory = 1;
	return (NULL);
}
