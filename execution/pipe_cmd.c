/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:07:31 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/13 16:20:25 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	child(t_cmd *cmd, t_env **env, t_exe_pipe *exec)
{
	char	*path;

	if (cmd->limiter)
		x_dup2(cmd->heredoc_fd, STDIN_FILENO);
	else if (cmd->infile)
		redirect_in(cmd->infile);
	else if (exec->prev_fd != -1)
		x_dup2(exec->prev_fd, STDIN_FILENO);
	if (cmd->next)
		x_dup2(exec->pipefd[1], STDOUT_FILENO);
	else if (cmd->out_file)
		redirect_out(cmd);
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	path = get_path(cmd->args[0], exec->envp);
	if (is_builtin(cmd->args[0]))
		exit(run_builtin(cmd, env));
	else
		execve(path, cmd->args, exec->envp);
	printf("minishell: %s: command not found\n", cmd->args[0]);
	free(path);
	exit(127);
}

void	close_wait(t_env **env, t_exe_pipe *exec)
{
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	free_args(exec->envp);
	waitpid(exec->last_pid, &exec->status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(exec->status))
		(*env)->exit_status = WEXITSTATUS(exec->status);
	else if (WIFSIGNALED(exec->status))
		(*env)->exit_status = 128 + WTERMSIG(exec->status);
}

void	execute_pipe(t_cmd *cmd, t_env **env)
{
	t_exe_pipe	exec;

	exec.envp = env_list_to_array(env);
	exec.prev_fd = -1;
	exec.last_cmd = cmd;
	while(exec.last_cmd->next)
		exec.last_cmd = exec.last_cmd->next;
	while(cmd)
	{
		x_pipe(exec.pipefd);
		exec.pid = fork();
		if (!exec.pid)
			child(cmd, env, &exec);
		if (exec.prev_fd != -1)
			close(exec.prev_fd);
		close(exec.pipefd[1]);
		exec.prev_fd = exec.pipefd[0];
		if (cmd == exec.last_cmd)
			exec.last_pid = exec.pid;
		cmd = cmd->next;
	}
	close_wait(env, &exec);
}
