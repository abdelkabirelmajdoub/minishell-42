#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env *envp = creat_env(env);
	t_cmd *cmds;
	inc_lvl(&envp);
	while (1)
	{
		char *input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (!input)
			break; 
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		add_history(input);
		t_token *tokens = tokenize(input);
		if (!tokens)
		{
			free(input);
			continue;
		}
		if (handle_syn(input, tokens))
		{
			cmds = pars_token(tokens);
			if (cmds)
				exe(cmds, env, &envp);
			free(cmds);
		}
		free(tokens);
		free(input);
	}
	clear_history();
	(void)ac;
	(void)av;
	return (0);
}
