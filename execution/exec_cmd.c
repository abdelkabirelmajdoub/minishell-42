/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:35:03 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/04 10:47:45 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	redirect_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0777);
	if (fd < 0)
	{
		perror("infile error");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 error");
		close(fd);
		exit(1);
	}
	close(fd);
}
void	redirect_out(char *filename, char *append)
{
	int	fd;

	if (append)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("outfile error");
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 error");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	execute_one(t_cmd *cmd, t_env **env, char **v_tmp)
{
	pid_t	pid;
	
	if (is_builtin(cmd->args[0]))
	{
		run_builtin(cmd, env);
		return;
	}
	pid = fork();
	if (!pid)
	{
		if (cmd->limiter)
			handle_heredoc(cmd);
		else if (cmd->infile)
			redirect_in(cmd->infile);
		if (cmd->out_file)
			redirect_out(cmd->out_file, cmd->append);
		execve(get_path(cmd->args[0], v_tmp), cmd->args, v_tmp);
		printf("command not found: %s\n", cmd->args[0]);
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
}

void	execute_pipe(t_cmd *cmd, t_env **env, char **v_tmp)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while(cmd)
	{
		if (pipe(pipefd) == -1) perror("pipe"), exit(1);
		pid = fork();
		if (!pid)
		{
			if (cmd->limiter)
				handle_heredoc(cmd);
			else if (cmd->infile)
				redirect_in(cmd->infile);
			else if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			if (cmd->next)
				dup2(pipefd[1], STDOUT_FILENO);
			else if (cmd->out_file)
				redirect_out(cmd->out_file, cmd->append);
			close(pipefd[0]);
			close(pipefd[1]);
			if (is_builtin(cmd->args[0]))
				exit(run_builtin(cmd, env));
			else
				execve(get_path(cmd->args[0], v_tmp), cmd->args, v_tmp);
			printf("command not found: %s\n", cmd->args[0]);
			exit(1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		close(pipefd[1]);
		prev_fd = pipefd[0];
		cmd = cmd->next;
	}
	while(wait(NULL) > 0);
}

int	is_pipe(t_cmd *cmd_list)
{
	return (cmd_list && cmd_list->next);
}

void	exe(t_cmd  *cmd_list, char **v_tmp, t_env **env)
{
	if (!cmd_list->args || !cmd_list->args[0]) 
	{
		if (cmd_list->limiter)
			run_heredoc(cmd_list->limiter, -1);
		return;
	}
	if (is_pipe(cmd_list))
		execute_pipe(cmd_list, env, v_tmp);
	else
		execute_one(cmd_list, env, v_tmp);
}