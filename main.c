#include "include/minishell.h"

void	set_terminal_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

void	setup_signals(void)
{
	set_terminal_echoctl();
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}


int	unclosed_quotes(const char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		i++;
	}
	if (quote != 0)
	{
		ft_putstr_fd("syntax error: unclosed quote\n", 2);
		return (0);
	}
	return (1);
}

void	process(t_env *envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		setup_signals();
		input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (!input)
		{
		    if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
		    exit (envp->exit_status);
		}
		if (input)
			add_history(input);
		if (!unclosed_quotes(input))
		{
			free(input);
			continue;
		}
		tokens = tokenize(input, envp);
		handle_quotes(tokens);
		expend_token(tokens, envp);
		if (!handle_syn(input, tokens))
		{
			free_tokens(tokens);
			free(input);
			continue;
		}
		cmds = pars_token(tokens);
		if (!cmds)
		{
			free(input);
			continue;
		}
		free_tokens(tokens);
		exe(cmds, &envp);
		free_cmd(cmds);
		free(input);
	}
}
int	main(int ac, char **av, char **env)
{
	t_env	*envp;

	envp = creat_env(env);
	inc_lvl(&envp);	
	process(envp);
	clear_history();
	(void)ac;
	(void)av;
	return (0);
}