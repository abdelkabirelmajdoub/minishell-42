/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:35:03 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/13 10:30:36 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	child_proc(t_cmd *cmd, char **envp)
{
	char	*path;

	if (cmd->limiter)
		dup2(cmd->heredoc_fd, STDIN_FILENO);
	else if (cmd->infile)
		redirect_in(cmd->infile);
	if (cmd->out_file)
		redirect_out(cmd->out_file, cmd->append);
	path = get_path(cmd->args[0], envp);
	execve(path, cmd->args, envp);
	printf("minishell: %s: command not found\n", cmd->args[0]);
	free(path);
	exit(127);
}

void	execute_one(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	char	**envp;
	int		status;
	
	if (is_builtin(cmd->args[0]))
	{
		status = run_builtin(cmd, env);
		(*env)->exit_status = status;
		return;
	}
	envp = env_list_to_array(env);
	pid = fork();
	if (!pid)
		child_proc(cmd, envp);
	free_args(envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*env)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*env)->exit_status = 128 + WTERMSIG(status);
}

void	execute_pipe(t_cmd *cmd, t_env **env)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	char	*path;
	char	**envp;
	int		status;
	pid_t	last_pid;
	t_cmd	*last_cmd;

	last_cmd = cmd;
	while(last_cmd->next)
		last_cmd = last_cmd->next;

	envp = env_list_to_array(env);
	prev_fd = -1;
	while(cmd)
	{
		if (pipe(pipefd) == -1) perror("pipe"), exit(1);
		pid = fork();
		if (!pid)
		{
			if (cmd->limiter)
				dup2(cmd->heredoc_fd, STDIN_FILENO);
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
			path = get_path(cmd->args[0], envp);
			if (is_builtin(cmd->args[0]))
				exit(run_builtin(cmd, env));
			else
				execve(path, cmd->args, envp);
			printf("minishell: %s: command not found\n", cmd->args[0]);
			free(path);
			exit(127);
		}
		if (prev_fd != -1)
			close(prev_fd);
		close(pipefd[1]);
		prev_fd = pipefd[0];
		if (cmd == last_cmd)
			last_pid = pid;
		cmd = cmd->next;
	}
	free_args(envp);
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		(*env)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*env)->exit_status = 128 + WTERMSIG(status);
}

void exe(t_cmd  *cmd_list, t_env **env)
{
	prepare_heredocs(cmd_list);
	if (is_pipe(cmd_list))
		execute_pipe(cmd_list, env);
	else
		execute_one(cmd_list, env);
}
