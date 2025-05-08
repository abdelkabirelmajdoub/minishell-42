CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRC = parsing/tokenize.c parsing/tokenize_utils.c parsing/tokenize_pars.c  \
	parsing/handle_errors.c parsing/handle_var.c \
	execution/exec_cmd.c execution/utils.c execution/heredoc.c\
	built-in/env.c  built-in/cd.c built-in/unset.c \
	built-in/exit.c built-in/export.c built-in/echo.c \
	built-in/run_built.c built-in/pwd.c main.c \

OBJ = $(SRC:.c=.o)
NAME = minishell
LIBFT =  libft/libft.a
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@make clean
clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re : fclean all