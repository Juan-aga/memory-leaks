/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_leaks.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:46:43 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/26 18:28:49 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_LEAKS_H
# define FT_MEMORY_LEAKS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/resource.h>

# define malloc(X) ft_alloc(X, __FILE__, __LINE__, __FUNCTION__, NULL, 0)
# define free(X) ft_alloc(0, __FILE__, __LINE__, __FUNCTION__, X, 1)
# define ft_memory_leaks ft_exit

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
}	t_malloc;

typedef struct s_mem_check
{
	struct rlimit	*max_proc;
//	pid_t			pid;
//	int				order;
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

//extern void	*__libc_malloc(size_t size);
//extern void *__libc_free(void *to_free);
void		*ft_alloc(size_t size, const char *file, int line, const char *func, void *free, int control);
void		ft_exit(void);
void		*ft_check_at_exit(t_mem_check *mem_check, int *fill_check_memory);

/*		t_malloc list functions		*/
t_malloc	*ft_malloc_new(t_mem_data data);
t_malloc	*ft_malloc_last(t_malloc *lst);
void		ft_malloc_add_back(t_malloc **lst, t_malloc *new);
int			ft_malloc_size(t_malloc *lst);
void		ft_malloc_delone(t_malloc **lst);
void		ft_malloc_clear(t_malloc *lst);
/*		utils						*/
char		*ft_ptoa(unsigned long long n);
#endif
