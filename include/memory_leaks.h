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

# define malloc(X) ft_alloc(X, __FILE__, __LINE__, __FUNCTION__, NULL, 0)
# define calloc(X, Y) ft_alloc(X * Y, __FILE__, __LINE__, __FUNCTION__, NULL, 1)
# define free(X) ft_alloc(0, __FILE__, __LINE__, __FUNCTION__, X, 2)
# define ft_memory_leaks ft_exit
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

void		*ft_alloc(size_t size, const char *file, int line,
				const char *func, void *free, int control);
void		ft_exit(void);
void		*ft_check_at_exit(t_mem_check *mem_check, int *fill_check_memory);
void	ft_report(t_mem_check *mem_check, t_mem_report *mem_report);

/*		at exit utils				*/
void	ft_count_alloc(t_malloc *lst1, t_malloc *lst2);
void	ft_count_free(t_mem_check *mem_check);
int		ft_strcmp(char *s1, char *s2);

/*		functions depends of system	*/
void		*ft_real_malloc(size_t size);
void		*ft_real_calloc(size_t size);
void		ft_real_free(void *p);

/*		t_malloc list functions		*/
t_malloc	*ft_malloc_new(t_mem_data data);
t_malloc	*ft_malloc_last(t_malloc *lst);
void		ft_malloc_add_back(t_malloc **lst, t_malloc *new);
int			ft_malloc_size(t_malloc *lst);
void		ft_malloc_delone(t_malloc *lst);
void		ft_malloc_clear(t_malloc *lst);
/*		utils						*/
char		*ft_ptoa(unsigned long long n);
char		*ft_itoa_unsigned(int n);
#endif
