#include "include/minishell.h"

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

void	handle_sigint_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal_prompt(void)
{
	signal(SIGINT, handle_sigint_prompt);
	signal(SIGQUIT, SIG_IGN);  // Ignore Ctrl-
}


int	main(int ac, char **av, char **env)
{
	t_env *envp;

	envp = creat_env(env);
	inc_lvl(&envp);	
	while (1)
	{
		// set_signal_prompt();
		char *input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (!input)
		{
		    if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		    exit (envp->exit_status);
		}
		if (input)
			add_history(input);
		t_token *tokens = tokenize(input, envp);
		handle_quotes(tokens);
		expend_token(tokens, envp);
		if (!handle_syn(input, tokens))
			continue;
		t_cmd *cmds = pars_token(tokens);

		if (!cmds)
			continue;
		free_tokens(tokens);

		
		exe(cmds, &envp);
		free_cmd(cmds);
		free(input);

	}

	clear_history();
	(void)ac;
	(void)av;
	return (0);
}