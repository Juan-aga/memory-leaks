/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_leaks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:46:43 by juan-aga          #+#    #+#             */
/*   Updated: 2023/03/01 09:43:15 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_LEAKS_H
# define MEMORY_LEAKS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/resource.h>

# define malloc(X) mem_leak_alloc(X, __FILE__, __LINE__, __FUNCTION__, NULL, 0)
# define calloc(X, Y) mem_leak_alloc(X * Y, __FILE__, __LINE__, __FUNCTION__, NULL, 1)
# define free(X) mem_leak_alloc(0, __FILE__, __LINE__, __FUNCTION__, X, 2)
# define mem_leak_exit mem_leak_exit
/*	if LOG is 1 it does the report to file
	if LOG is 0 show the report in the screem */
# ifndef LOG
#  define LOG 0
# endif

typedef struct s_malloc
{
	size_t			size;
	int				line;
	const char		*file;
	const char		*func;
	char			*p;
	void			*alloc;
	struct s_malloc	*next;
	struct s_malloc	*prev;
	int				num_free;
	int				num_alloc;
}	t_malloc;

typedef struct s_mem_check
{
	struct rlimit	*max_proc;
	t_malloc		*free;
	t_malloc		*alloc;
}	t_mem_check;

typedef struct s_mem_data
{
	size_t			size;
	int				line;
	const char		*file;
	const char		*func;
	void			*alloc;
	char			*p;
}	t_mem_data;

typedef struct s_mem_report
{
	int	leaks;
	int	double_free;
	int	not_allocated;
}	t_mem_report;

void		*mem_leak_alloc(size_t size, const char *file, int line,
				const char *func, void *free, int control);
void		mem_leak_exit(void);
void		*mem_leak_check_at_exit(t_mem_check *mem_check, int *fill_check_memory);
void	mem_leak_report(t_mem_check *mem_check, t_mem_report *mem_report);

/*		at exit utils				*/
void	mem_leak_count_alloc(t_malloc *lst1, t_malloc *lst2);
void	mem_leak_count_free(t_mem_check *mem_check);
int		mem_leak_strcmp(char *s1, char *s2);

/*		functions depends of system	*/
void		*mem_leak_real_malloc(size_t size);
void		*mem_leak_real_calloc(size_t size);
void		mem_leak_real_free(void *p);

/*		t_malloc list functions		*/
t_malloc	*mem_leak_malloc_new(t_mem_data data);
t_malloc	*mem_leak_malloc_last(t_malloc *lst);
void		mem_leak_malloc_add_back(t_malloc **lst, t_malloc *new);
int			mem_leak_malloc_size(t_malloc *lst);
void		mem_leak_malloc_delone(t_malloc *lst);
void		mem_leak_malloc_clear(t_malloc *lst);
/*		utils						*/
char		*mem_leak_ptoa(unsigned long long n);
char		*mem_leak_itoa_unsigned(int n);
#endif
