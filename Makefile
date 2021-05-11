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
					utils_mem.c \
					signals.c \
					utils_env.c \
					utils_env2.c \
					builtins/cd.c \
					builtins/echo.c \
					builtins/env.c \
					builtins/exit.c \
					builtins/export.c \
					builtins/pwd.c \
					builtins/unset.c \
					builtins/history_builtin.c \
					initializations.c \
					input/termios.c \
					input/utils_input.c \
					input/termcaps.c \
					input/input.c \
					input/history.c \
					parsing/tokenizer.c \
					parsing/utils_quoting.c \
					parsing/types.c \
					parsing/parsing_errors.c \
					parsing/utils_parsing.c \
					parsing/utils_exclusions.c

TEST_SRCS		=	parsing/parsing_basic.c \
					parsing/parsing_basic_pipe.c \
					parsing/parsing_basic_redir_sup.c \
					parsing/parsing_basic_redir_inf.c \
					parsing/parsing_basic_redir_dsup.c \
					parsing/parsing_complex_redir.c \
					parsing/parsing_negatives.c \
					parsing/parsing_escaped.c \
					parsing/parsing_err_esc.c \
					parsing/parsing_err_smc.c \
					parsing/parsing_err_pipe.c \
					parsing/parsing_err_redirs.c \
					env_utils_test.c unset_test.c utils_test.c cd_test.c echo_test.c #signal_tests.c

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}
TEST_OBJS		=	${addprefix tests/,${TEST_SRCS:.c=.o}}
NO_MAIN			=	$(filter-out srcs/main.o,$(OBJS))

LD_FLAGS		=	-L libft

HEAD			=	-I includes -I libft

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra -g #-fsanitize=address

CRITERIONFLAGS	=	-lcriterion

.c.o			:
					@${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					make -C libft
					@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} -lft -lncurses

all				:	${NAME}

val				:	${NAME}
					valgrind --leak-check=full --tool=memcheck --show-reachable=yes \
						--errors-for-leak-kinds=all \
						--show-leak-kinds=all \
						--suppressions=tests/assets/termcaps_suppression \
						--error-exitcode=42 ./minishell

test			:	$(TEST_NAME)
					@./${TEST_NAME}
					@rm $(TEST_NAME)

$(TEST_NAME)	:	$(NO_MAIN) ${TEST_OBJS} ${NAME}
					@${CC} -g $(NO_MAIN) ${CFLAGS} ${LD_FLAGS} ${TEST_OBJS} ${CRITERIONFLAGS} -o ${TEST_NAME} \
						-lft -lncurses -Itests
					@ rm $(TEST_OBJS) $(NO_MAIN)
					@clear


clean			:
					make clean -C libft
					@rm -rf ${OBJS}

fclean			:	clean
					make fclean -C libft
					@rm -rf ${NAME} $(TEST_NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
