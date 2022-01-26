# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ephantom <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 20:22:55 by ephantom          #+#    #+#              #
#   Updated: 2022/01/17 15:24:34 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	init.c	main.c	time.c	utils.c	life.c

OBJS	=	${SRCS:%.c=%.o}

HEADER	=	philo.h

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I${HEADER}

RM		=	 rm -f

.PHONY:		all clean fclean re

all:		${NAME}

%.o: 		%.c ${HEADER}
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all