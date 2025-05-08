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
	t_env *envp = creat_env(env);
	t_cmd *cmds;

	inc_lvl(&envp);
	cmds = NULL;
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
			// free_cmd(cmds);
		}

		free_tokens(tokens);
		free(input);
		system("leaks -q minishell");
	}
	(void)av;
	(void)ac;
	clear_history();
	free_env(envp);
	return (0);
}
