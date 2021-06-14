NAME			=	minishell

TEST_NAME		=	minishell_test

SRCS			=	main.c \
					system/minishell_entry.c \
					system/signals.c \
					system/init_shlvl_path_env.c \
					debug/debug.c \
					debug/utils.c \
					env/parse_env.c \
					env/utils_env.c \
					env/utils_mem_env.c \
					builtins/cd.c \
					builtins/echo.c \
					builtins/env.c \
					builtins/exit.c \
					builtins/export.c \
					builtins/pwd.c \
					builtins/unset.c \
					builtins/history_builtin.c \
					utils/utils.c \
					utils/utils_mem.c \
					utils/initializations.c \
					utils/errors.c \
					input/prompt.c \
					input/termios.c \
					input/utils_input.c \
					input/termcaps.c \
					input/input.c \
					input/history.c \
					input/cursor_utils.c \
					input/move_cursor.c \
					parsing/old_parse.c \
					parsing/tokenizer.c \
					parsing/utils_quoting.c \
					parsing/types.c \
					parsing/parsing_errors.c \
					parsing/utils_parsing.c \
					parsing/utils_exclusions.c \
					parsing/utils_d_quote.c \
					exec/exec.c \
					exec/bin_builtins.c \
					exec/path_utils.c \
					exec/exec2.c \
					exec/rearrange_lists.c \
					exec/redirections.c \
					exec/perform_execution.c \
					exec/utils_pipeline.c \
					exec/pipe.c \
					exec/utils_fds.c \
					exec/pipeline_redirs.c \
					exec/exec_for_pipeline.c \
					expansion/expansion2.c \
					expansion/utils_concat.c \
					expansion/utils_expansion.c \
					expansion/expand_pipeline.c

TEST_SRCS		=	execution/path_type_parser.c \
					env_utils_test.c unset_test.c utils_test.c cd_test.c echo_test.c \
					exit_test_messages.c \
					exit_test_codes.c \
					#signal_tests.c
					#parsing/parsing_basic.c \
					#parsing/parsing_basic_pipe.c \
					#parsing/parsing_basic_redir_sup.c \
					#parsing/parsing_basic_redir_inf.c \
					#parsing/parsing_basic_redir_dsup.c \
					#parsing/parsing_complex_redir.c \
					#parsing/parsing_err_esc.c \
					#parsing/parsing_err_smc.c \
					#parsing/parsing_err_pipe.c \
					#parsing/parsing_err_redirs.c \
					#parsing/parsing_negatives.c \
					#parsing/parsing_escaped.c

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
					printf "$(GREEN)█"

$(NAME)			:	compile ${OBJS} done
					make -C libft
					@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} -lft -lncurses

all				:	${NAME}

val				:	${NAME}
					valgrind \
					--leak-check=full --tool=memcheck \
					--show-reachable=yes \
					--track-fds=yes \
					--suppressions=tests/assets/suppressions_valgrind \
					--errors-for-leak-kinds=all \
					--show-leak-kinds=all --error-exitcode=1 ./minishell

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

.SILENT:

BLUE	= \033[1;34m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
DEFAULT = \033[0m

compile	:
			echo "\n$(YELLOW)[X] Compiling $(BLUE)Minishell$(DEFAULT)\n"
done	:
			echo "$(GREEN) => 100%$(DEFAULT)\n"
