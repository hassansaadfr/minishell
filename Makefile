NAME			=	minishell

SRCS			=	main.c \
					system/minishell_entry.c \
					system/signals.c \
					system/init_shlvl_path_env.c \
					system/sig_err_msgs.c \
					debug/debug.c \
					debug/debug2.c \
					debug/utils.c \
					env/parse_env.c \
					env/utils_env.c \
					env/utils_mem_env.c \
					builtins/cd.c \
					builtins/echo.c \
					builtins/env.c \
					builtins/exit.c \
					builtins/export.c \
					builtins/export_utils.c \
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
					pipes/utils_pipeline.c \
					pipes/pipe.c \
					pipes/utils_fds.c \
					pipes/pipeline_redirs.c \
					pipes/exec_for_pipeline.c \
					expansion/expansion2.c \
					expansion/utils_concat.c \
					expansion/utils_expansion.c \
					expansion/expand_pipeline.c

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}

LD_FLAGS		=	-L libft

HEAD			=	-I includes -I libft

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra

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
					--errors-for-leak-kinds=all \
					--show-leak-kinds=all --error-exitcode=1 ./minishell

clean			:
					make clean -C libft
					@rm -rf ${OBJS}

fclean			:	clean
					make fclean -C libft
					@rm -rf ${NAME}

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
