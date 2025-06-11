/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:07:45 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/11 14:40:44 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_heredoc(char *limiter, int w_end, t_env **env)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		line = expand_variable(line, *env);
		if (!line || !ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(w_end, line, ft_strlen(line));
		write(w_end, "\n", 1);
		free(line);
	}
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
	else if (sig == SIGQUIT)
		return ;
}

void	set_heredoc(void)
{
	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, heredoc_sig);
}

void	heredoc_child(t_cmd *cmd, pid_t pid, int *here_pipe, t_env **env)
{
	if (pid == 0)
	{
		set_heredoc();
		close(here_pipe[0]);
		run_heredoc(cmd->limiter, here_pipe[1], env);
		close(here_pipe[1]);
		exit(0);
	}
	close(here_pipe[1]);
	cmd->heredoc_fd = here_pipe[0];
}

int	prepare_heredocs(t_cmd *cmd_list, t_env **env)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		here_pipe[2];
	int		stat;

	cmd = cmd_list;
	cmd->heredoc_fd = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd)
	{
		if (cmd->limiter)
		{
			x_pipe(here_pipe);
			pid = fork();
			heredoc_child(cmd, pid, here_pipe, env);
			waitpid(pid, &stat, 0);
			if (WIFEXITED(stat) && WEXITSTATUS(stat) == 1)
				return (close(here_pipe[0]), (*env)->exit_status = 1, 1);
		}
		cmd = cmd->next;
	}
	return (0);
}
