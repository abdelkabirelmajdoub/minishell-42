CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRC = parsing/tokenize.c execution/exec_cmd.c execution/utils.c 
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