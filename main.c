#include "include/minishell.h"



int	main(int ac, char **av, char **env)
{
	t_env *envp;
	char *input;
	t_cmd *cmds;

	envp = creat_env(env);
	inc_lvl(&envp);	
		while (1)
	{
		input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (!input)
		{
			free_env(envp);
			write(1, "exit\n", 5);
			exit(0);
		}
		if (*input)
			add_history(input);

		t_token *tokens = tokenize(input);
		handle_quotes(tokens);
		expend_token(tokens, envp);
		if (!handle_syn(input, tokens))
		{
			free(input);
			free_tokens(tokens);
			continue;
		}
		free(input);
		cmds = pars_token(tokens);
		if (!cmds)
			continue;
		exe(cmds, &envp);	
		free_cmd(cmds);
		free_tokens(tokens);
	}
	free_env(envp);
	clear_history();
	(void)ac;
	(void)av;
	return (0);
}

/*
To fix:
cd ~/Desktop fixed




*/