/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:41:14 by juan-aga          #+#    #+#             */
/*   Updated: 2023/02/26 01:37:15 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ft_memory_leaks.h"
//#define malloc(X) malloc_42( X, __FILE__, __LINE__, __FUNCTION__)
/*void *my_malloc(size_t size, const char *file, int line, const char *func);
extern void *__libc_malloc(size_t size);

typedef struct s_malloc
{
	size_t	size;
	const char *file;
	int			line;
	const char	*func;
	void		*p;
}	t_malloc;

int check = 1;

void	*my_malloc_hook(t_malloc m)
{
	void	*result;
	pid_t	process;


	result = malloc(m.size);
	process = getpid ();
	check = 1;
	printf("puntero %p allocado en %s %s:%i process: %i\n", result, m.file, m.func, m.line, process);
	return (result);
}


void *my_malloc(size_t size, const char *file, int line, const char *func)
{

	t_malloc	m;
	
	if (check)
	{
		check = 0;
		m.size = size;
		m.file = file,
		m.line = line;
		m.func = func;
		return (my_malloc_hook(m));
	}
	return (__libc_malloc(size));
//	char *cal = __builtin_return_FUNTION();
//	printf("\n%x\n", caller);
//	printf("entre\t %p file: %s %s:%i\n", caller, file , func, line);

   Link List functionality goes in here

//    return p;
}
*/

void	ft_print(void)
{
	printf("\nexit\n");
//	return (NULL);
}
int main(int argc, char *argv[])
{
	pid_t	f;
	void	*z;
//atexit(ft_memory_leaks);
//atexit(ft_print);
	f=fork();
	if (f != 0)
	{
printf("entra en fork\n");
malloc(5);
for (int j = 0; j < 5; j++)
malloc(100);            /* Never freed--a memory leak */
//calloc(16, 16);            /* Never freed--a memory leak */
//check=0;
//ft_memory_leaks;
exit(0);
}
printf("sele del fork\n");
for (int j = 0; j < 5; j++)
{
z = malloc(100);            /* Never freed--a memory leak */
//free(z);
}
for (int j = 0; j < 5; j++)
malloc(100);
//ft_memory_leaks;
return (0);
}
