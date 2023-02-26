# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 12:58:20 by juan-aga          #+#    #+#              #
#    Updated: 2023/02/26 18:29:55 by juan-aga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_memory_leaks.a

CC			= gcc ${CFLAGS} ${HEADERS}

AR			= ar -rcs

CFLAGS		= -Wall -Wextra -Werror 
RM			= rm -Rf

SRC_DIR		= src/

OBJ_DIR		= obj/

_SRC		= 42memory_leaks.c		\
			  ft_malloc_lst.c		\
			  ft_malloc_lst_del.c	\
			  ptoa.c				\
			  ft_at_exit.c

SRC			= ${addprefix ${SRC_DIR}, ${_SRC}}

OBJ			= ${patsubst ${SRC_DIR}%.c, ${OBJ_DIR}%.o, ${SRC}}

HEADERS		= -I include/

ifdef D
	CFLAGS += -g
endif

#		COLORS		#
CYELLOW			=\033[1;33m
CGREEN			=\033[0;32m
CRED			=\033[0;91m
CRESET			=\033[0m

${OBJ_DIR}%.o: ${SRC_DIR}%.c
			@mkdir -p obj
			@${CC} ${CFLAGS} -c $<  -o $@ && printf "${CGREEN}Compiling: ${CYELLOW}$(notdir $<\n)"

all:		${NAME}

${NAME}:	${OBJ}
			@${AR} ${NAME} ${OBJ}
			@echo "\n${CYELLOW}${NAME}${CGREEN} compiled with flags: ${CYELLOW}${CFLAGS}\n${CRESET}"

clean:
			@${RM} ${OBJ_DIR}
			@echo "${CRED}${NAME} objects files were deleted.${CRESET}"

fclean:		clean
			@${RM} ${NAME}
			@echo "${CRED}${NAME} was deleted.${CRESET}"

re:			fclean all

.PHONY:		all clean fclean re bonus
