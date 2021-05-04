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
					builtins/history_builtin.c \
					utils_mem.c \
					signals.c \
					utils_env.c \
					utils_env2.c \
					termios.c \
					initializations.c \
					utils_input.c \
					termcaps.c \
					buffer.c \
					history.c

TEST_SRCS		=	cd_test.c env_utils_test.c unset_test.c echo_test.c #signal_tests.c

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}
TEST_OBJS		=	${addprefix tests/,${TEST_SRCS:.c=.o}}
NO_MAIN			=	$(filter-out srcs/main.o,$(OBJS))

LD_FLAGS		=	-L libft

HEAD			=	-I includes -I libft

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra -g -fsanitize=address

CRITERIONFLAGS	=	-lcriterion

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					make -C libft
					@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} -lft -lncurses

all				:	${NAME}

test			:	$(TEST_NAME)
					./${TEST_NAME}
					@rm $(TEST_NAME)

$(TEST_NAME)	:	$(NO_MAIN) ${TEST_OBJS} ${NAME}
					@${CC} -g $(NO_MAIN) ${CFLAGS} ${LD_FLAGS} ${TEST_OBJS} ${CRITERIONFLAGS} -o ${TEST_NAME} \
						-lft -lncurses
					@ rm $(TEST_OBJS) $(NO_MAIN)

clean			:
					make clean -C libft
					@rm -rf ${OBJS}

fclean			:	clean
					make fclean -C libft
					@rm -rf ${NAME} $(TEST_NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
