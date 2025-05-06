#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env *envp = creat_env(env);
<<<<<<< HEAD

	inc_lvl(&envp);
=======
	
>>>>>>> 1327811c29cb9bb34480570258e04fd8403de2ff
	while (1)
	{
		char *input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (input)
			add_history(input);
		t_token *tokens = tokenize(input);
		handle_syn(input, tokens);
		t_cmd *cmds = pars_token(tokens);

		if (!cmds)
			continue;;
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
