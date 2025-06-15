CC      = cc
CFLAGS  = -Wall -Wextra -Werror
SRC     = parsing/tokenize1.c parsing/tokenize_utils.c parsing/tokenize_pars.c \
		  parsing/tokenize_pars2.c parsing/tokenize2.c parsing/tokenize3.c parsing/tokenize4.c \
          parsing/handle_errors.c parsing/handle_var1.c parsing/handle_var2.c\
		  parsing/handle_var3.c parsing/handle_var4.c \
          execution/exec_cmd.c execution/utils.c execution/heredoc.c \
		  execution/io_file.c execution/pipe_cmd.c \
          built-in/env.c built-in/cd.c built-in/unset.c \
          built-in/exit.c built-in/export.c  built-in/expo_utils.c built-in/echo.c \
          built-in/run_built.c built-in/pwd.c \
          main.c env/cnv_env_arr.c env/env_tools.c cleanup/cleanup.c signal.c

OBJ     = $(SRC:.c=.o)
NAME    = minishell
LIBFT   = libft/libft.a


all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[1;32m                       🚧  Building MINISHELL... 🚧                        \033[0m"
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline  -o $(NAME)

%.o:%.c include/minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
