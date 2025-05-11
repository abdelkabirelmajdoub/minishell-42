CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRC = parsing/tokenize.c parsing/tokenize_utils.c parsing/tokenize_pars.c  \
	parsing/handle_errors.c parsing/handle_var.c \
	execution/exec_cmd.c execution/utils.c execution/heredoc.c\
	built-in/env.c  built-in/cd.c built-in/unset.c \
	built-in/exit.c built-in/export.c built-in/echo.c \
	built-in/run_built.c built-in/pwd.c main.c env/cnv_env_arr.c env/env_tools.c \

OBJ = $(SRC:.c=.o)
NAME = minishell
LIBFT =  libft/libft.a
all: $(NAME)

$(NAME): $(OBJ)
	# @make -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@make clean
clean:
	# @make clean -C libft
	@rm -rf $(OBJ)
fclean: clean
	# @make fclean -C libft
	@rm -rf $(NAME)
re : fclean all