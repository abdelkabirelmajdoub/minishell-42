/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:07:45 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/08 12:39:26 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_heredoc(char *limiter, int	write_end)
{
	char	*line;

	while(1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break;
		}
		write(write_end, line, ft_strlen(line));
		write(write_end, "\n", 1);
		free(line);
	}
}

void prepare_heredocs(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		here_pipe[2];

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->limiter)
		{
			if (pipe(here_pipe) == -1)
			{
				perror("heredoc pipe");
				exit(1);
			}
			pid = fork();
			if (pid == 0)
			{
				close(here_pipe[0]);
				run_heredoc(cmd->limiter, here_pipe[1]);
				close(here_pipe[1]);
				exit(0);
			}
			close(here_pipe[1]);
			waitpid(pid, NULL, 0);
			cmd->heredoc_fd = here_pipe[0];
			close(here_pipe[0]);
		}
		cmd = cmd->next;
	}
}
