#ifndef CONSTANTS_H

# define CONSTANTS_H

# define INPUT_MAX 4096
# define ENTER '\n'
# define DELETE 127
# define ESCAPE 27

# define UP_ARROW 12938712
# define DN_ARROW 1290837

# define DEBUG 1

# define ARG_NUMERIC_FR "argument numérique nécessaire"
# define ARG_NUMERIC_EN "numeric argument required"

# define TOO_MUCH_ARGS_FR "trop d'arguments"
# define TOO_MUCH_ARGS_EN "too many arguments"

enum	e_err_msg_exit
{
	ARG_NUMERIC,
	TOO_MUCH_ARGS
};

#endif
