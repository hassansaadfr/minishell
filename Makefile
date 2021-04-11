# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsaadaou <hsaadaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 12:45:43 by hsaadaou          #+#    #+#              #
#    Updated: 2021/04/11 12:29:25 by hsaadaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

TEST_NAME		=	minishell_test

SRCS			=	main.c \
					parse.c \
					utils.c \
					exec.c \
					debug.c \
					prompt.c \
					bin_builtins.c \
					bin_paths.c \
					bin_bins.c \
					builtins/cd.c \
					builtins/echo.c \
					builtins/env.c \
					builtins/exit.c \
					builtins/export.c \
					builtins/pwd.c \
					builtins/unset.c \
					utils_mem.c \
					utils_env.c

TEST_SRCS		=	cd_test.c env_utils_test.c

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}
TEST_OBJS		=	${addprefix tests/,${TEST_SRCS:.c=.o}}
NO_MAIN			=	$(filter-out srcs/main.o,$(OBJS))

LD_FLAGS		=	-L libft

HEAD			=	-I includes -I libft

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra -g

CRITERIONFLAGS	=	-lcriterion

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					make -C libft
					@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} -lft

all				:	${NAME}

test			:	$(TEST_NAME)
					./${TEST_NAME}
					@rm $(TEST_NAME)

$(TEST_NAME)	:	$(NO_MAIN) ${TEST_OBJS} ${NAME}
					@${CC} $(NO_MAIN) ${CFLAGS} ${LD_FLAGS} ${TEST_OBJS} ${CRITERIONFLAGS} -o ${TEST_NAME} \
						-lft
					@ rm $(TEST_OBJS) $(NO_MAIN)

clean			:
					make clean -C libft
					@rm -rf ${OBJS}

fclean			:	clean
					make fclean -C libft
					@rm -rf ${NAME} $(TEST_NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
