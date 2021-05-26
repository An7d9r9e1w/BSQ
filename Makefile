# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnamor <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/22 21:11:06 by nnamor            #+#    #+#              #
#    Updated: 2021/03/24 10:16:29 by nnamor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c		\
		  algoritm.c	\
		  cvector.c		\
		  file.c		\
		  lines.c		\
		  map.c			\

OBJS	= ${SRCS:.c=.o}

NAME	= bsq

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
