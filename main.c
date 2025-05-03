#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env *envp = creat_env(env);

	while (1)
	{
		char *input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (input)
			add_history(input);

		t_token *tokens = tokenize(input);
		t_cmd *cmds = pars_token(tokens);

		exe(cmds, env, &envp);	

		free(cmds);
		free(tokens);
		free(input);
	}

	clear_history();
	(void)ac;
	(void)av;
	return (0);
}
