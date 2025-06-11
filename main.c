/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:48:19 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/11 15:10:16 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	prompt(char **input, t_env *envp)
{
	set_signals();
	*input = readline("\033[36mmini\033[31mshell$ \033[0m");
	if (!*input)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		exit(envp->exit_status);
	}
	if (*input)
		add_history(*input);
}

int	q_input(char *input)
{
	if (!unclosed_quotes(input))
	{
		free(input);
		return (0);
	}
	return (1);
}

int	parsing_execution(char *input, t_env **envp)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(input, *envp);
	handle_quotes(tokens);
	expend_token(tokens, *envp);
	if (!handle_syn(input, tokens))
	{
		free_tokens(tokens);
		free(input);
		return (0);
	}
	cmds = pars_token(tokens);
	if (!cmds)
	{
		free(input);
		return (0);
	}
	free_tokens(tokens);
	exe(cmds, envp);
	free_cmd(cmds);
	free(input);
	return (1);
}

void	process(t_env *envp)
{
	char	*input;

	while (1)
	{
		prompt(&input, envp);
		if (!q_input(input))
			continue ;
		if (!parsing_execution(input, &envp))
			continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*envp;

	envp = creat_env(env);
	inc_lvl(&envp);
	process(envp);
	clear_history();
	(void)ac;
	(void)av;
	return (0);
}
