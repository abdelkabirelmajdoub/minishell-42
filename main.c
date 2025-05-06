#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env *envp = creat_env(env);
	t_cmd *cmds;
	inc_lvl(&envp);
	while (1)
	{
		char *input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (input)
			add_history(input);
		cmds = NULL;
		t_token *tokens = tokenize(input);
		if (handle_syn(input, tokens))
		{
			cmds = pars_token(tokens);
			exe(cmds, env, &envp);	

			free(input);
			free(cmds);
			free(tokens);
		}
	}

	clear_history();
	(void)ac;
	(void)av;
	return (0);
}
