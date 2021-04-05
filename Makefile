# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 12:45:43 by hsaadaou          #+#    #+#              #
#    Updated: 2021/04/05 15:12:13 by hsaadaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCS			=	main.c

TEST_SRCS		=	simple.c

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}
TEST_OBJS		=	${addprefix tests/,${SRCS:.c=.o}}
NO_MAIN			=	$(filter-out main.o,$(OBJS))

HEAD			=	-I includes

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra

CRITERIONFLAGS	=	-lcriterion

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					@${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all				:	${NAME}

test			:	${OBJS} ${TEST_OBJS}
					@${CC} $(NO_MAIN) ${CFLAGS} ${TEST_OBJS} ${CRITERIONFLAGS} -o ${NAME}_test

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
