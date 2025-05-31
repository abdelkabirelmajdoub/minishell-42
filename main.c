#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env *envp;
	t_ex	*expand;

	expand = malloc(sizeof(t_ex));
	if (!expand)
		return (0);
	envp = creat_env(env);
	inc_lvl(&envp);	
	while (1)
	{
		char *input = readline("\033[36mmini\033[31mshell$ \033[0m");
		if (input)
			add_history(input);
		t_token *tokens = tokenize(input, envp, expand);
		handle_quotes(tokens);
		expend_token(tokens, envp, expand);
		if (!handle_syn(input, tokens))
			continue;
		t_cmd *cmds = pars_token(tokens);
		// printf("%s\n", cmds->args[0]);
		// printf("%d \n", tokens->type );
		if (!cmds)
			continue;
		free_tokens(tokens);
		exe(cmds, &envp);
		free_cmd(cmds);
		free(input);
		// system("leaks -q minishell");
	}
		free(expand);

	clear_history();
	(void)ac;
	(void)av;
	return (0);
}