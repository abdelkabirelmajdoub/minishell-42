#include "include/minishell.h"

void	free_tokens(t_token *tok)
{
	t_token *tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->value);
		free(tmp);
	}
}

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
		// system("leaks -q minishell");
		t_cmd *cmds = pars_token(tokens);
		if (!cmds)
			continue;
		exe(cmds, &envp);	

		free(cmds);
		free(tokens);
		free(input);
	}

	clear_history();
	(void)ac;
	(void)av;
	return (0);
}