#include "include/minishell.h"



int	main(int ac, char **av, char **env)
{
	t_env *envp;

	envp = creat_env(env);
	inc_lvl(&envp);	
	while (1)
	{
		char *input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (input)
			add_history(input);
		t_token *tokens = tokenize(input);
		handle_quotes(tokens);
		expend_token(tokens, envp);
		handle_syn(input, tokens);
		t_cmd *cmds = pars_token(tokens);
		// printf("%s %s\n", cmds->out_file[0], cmds->out_file[1]);
		if (!cmds)
			continue;
		exe(cmds, &envp);	

		// // free_tokens(tokens);
		// free_cmd(cmds);
		// free(input);
		// system("leaks -q minishell");
	}

	clear_history();
	(void)ac;
	(void)av;
	return (0);
}