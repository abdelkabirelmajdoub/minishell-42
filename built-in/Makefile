CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRC = env.c  main.c cd.c unset.c exit.c export.c echo.c
OBJ = $(SRC:.c=.o)
NAME = minishell
LIBFT =  ../libft/libft.a
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@make clean
	@./minishell
clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re : fclean all