# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 12:45:43 by hsaadaou          #+#    #+#              #
#    Updated: 2021/04/05 15:41:41 by hsaadaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

TEST_NAME		=	minishell_test

SRCS			=	main.c

TEST_SRCS		=	simple.c

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}
TEST_OBJS		=	${addprefix tests/,${TEST_SRCS:.c=.o}}
NO_MAIN			=	$(filter-out srcs/main.o,$(OBJS))

HEAD			=	-I includes

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra

CRITERIONFLAGS	=	-lcriterion

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					@${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all				:	${NAME}

test			:	$(TEST_NAME)
					./${TEST_NAME}
					@rm $(TEST_NAME)

$(TEST_NAME)	:	$(NO_MAIN) ${TEST_OBJS}
					@${CC} $(NO_MAIN) ${CFLAGS} ${TEST_OBJS} ${CRITERIONFLAGS} -o ${TEST_NAME}
					@ rm $(TEST_OBJS) $(NO_MAIN)

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
