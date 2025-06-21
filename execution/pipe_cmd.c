/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:07:31 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/21 15:36:42 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_new(t_cmd *cmd, t_exe_pipe *exec, t_env **env)
{
	char	*path;

	path = get_path(cmd->args[0], exec->envp);
	if (is_builtin(cmd->args[0]))
		exit(run_builtin(cmd, env));
	execve(path, cmd->args, exec->envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(path);
	exit(127);
}

void	child(t_cmd *cmd, t_env **env, t_exe_pipe *exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->limiter)
		x_dup2(cmd->heredoc_fd, STDIN_FILENO);
	else if (cmd->infile)
		redirect_in(cmd->infile);
	else if (exec->prev_fd != -1)
		x_dup2(exec->prev_fd, STDIN_FILENO);
	if (cmd->next && !cmd->out_file[0])
		x_dup2(exec->pipefd[1], STDOUT_FILENO);
	else if (cmd->out_file)
		redirect_out(cmd);
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	if (cmd->heredoc_fd > 0)
		close(cmd->heredoc_fd);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	cmd_new(cmd, exec, env);
}

void	close_wait(t_env **env, t_exe_pipe *exec)
{
	if (exec->prev_fd != -1)
	{
		close(exec->prev_fd);
		exec->prev_fd = -1;
	}
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	free_args(exec->envp);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(exec->last_pid, &exec->status, 0);
	while (wait(NULL) > 0)
		;
	if (exec->pid < 0)
		(*env)->exit_status = 1;
	else if (WIFEXITED(exec->status))
		(*env)->exit_status = WEXITSTATUS(exec->status);
	else if (WIFSIGNALED(exec->status))
	{
		(*env)->exit_status = 128 + WTERMSIG(exec->status);
		if (WTERMSIG(exec->status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	run_cmds(t_cmd *cmd, t_exe_pipe *exec, t_env **env)
{
	if (!exec->pid)
		child(cmd, env, exec);
	else
	{
		close(exec->pipefd[1]);
		if (exec->prev_fd != -1)
			close(exec->prev_fd);
		if (cmd->next)
			exec->prev_fd = exec->pipefd[0];
		else
			close(exec->pipefd[0]);
		if (cmd == exec->last_cmd)
			exec->last_pid = exec->pid;
		if (cmd->heredoc_fd > 0)
			close(cmd->heredoc_fd);
	}
}

void	execute_pipe(t_cmd *cmd, t_env **env)
{
	t_exe_pipe	exec;

	exec.envp = env_list_to_array(env);
	exec.prev_fd = -1;
	exec.last_cmd = cmd;
	while (exec.last_cmd->next)
		exec.last_cmd = exec.last_cmd->next;
	while (cmd)
	{
		exec.pipefd[0] = -1;
		exec.pipefd[1] = -1;
		x_pipe(exec.pipefd);
		exec.pid = fork();
		if (exec.pid < 0)
		{
			perror("fork");
			break ;
		}
		run_cmds(cmd, &exec, env);
		cmd = cmd->next;
	}
	close_wait(env, &exec);
}
