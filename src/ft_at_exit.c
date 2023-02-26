/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_at_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:15:41 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/26 18:36:12 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory_leaks.h"

static void	ft_count_free(t_mem_check *mem_check);
static int	ft_strcmp(char *s1, char *s2);


void	*ft_check_at_exit(t_mem_check *mem_check, int *fill_check_memory)
{
//	int			num_malloc;
//	int			num_free;
	t_malloc	*tmp;
	
//	waitpid((*mem_check)->pid, &num_free, 0);
	ft_count_free(mem_check);
	tmp = mem_check->alloc;
	printf("\texit process: \n");
	while (tmp)
	{
		printf("\t[%s] memory allocated at: %s %s:%i free num: %i\n", tmp->p, tmp->file, tmp->func, tmp->line, tmp->num_free);
		tmp = tmp->next;
	}
	tmp = mem_check->free;
	while (tmp)
	{
		printf("\t[%s] memory free at: %s %s:%i\n", tmp->p, tmp->file, tmp->func, tmp->line);
		tmp = tmp->next;
	}
	*fill_check_memory = 1;
	return (NULL);
}
static void	ft_count_free(t_mem_check *mem_check)
{
	t_malloc	*m;
	t_malloc	*f;

	m = mem_check->alloc;
	while (m)
	{
		f = mem_check->free;
		while (f)
		{
			if (!ft_strcmp(m->p, f->p))
				m->num_free += 1;
			f = f->next;
		}
		m = m->next;
	}
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	if (s1[i] == s2[i])
		return (0);
	return (1);
}
