#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env *envp;

	envp = creat_env(env);
	inc_lvl(&envp);	
	while (1)
	{
		char *input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (!input)
			exit(0);
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