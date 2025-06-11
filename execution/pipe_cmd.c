/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:07:31 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/11 14:51:30 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_nfound(char **args, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(path);
	exit(127);
}

void	child(t_cmd *cmd, t_env **env, t_exe_pipe *exec)
{
	char	*path;

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
	if (!cmd->args || !cmd->args[0])
		exit(0);
	path = get_path(cmd->args[0], exec->envp);
	if (is_builtin(cmd->args[0]))
		exit(run_builtin(cmd, env));
	else
		execve(path, cmd->args, exec->envp);
	cmd_nfound(cmd->args, path);
}

void	close_wait(t_env **env, t_exe_pipe *exec)
{
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	free_args(exec->envp);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(exec->last_pid, &exec->status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(exec->status))
		(*env)->exit_status = WEXITSTATUS(exec->status);
	else if (WIFSIGNALED(exec->status))
		(*env)->exit_status = 128 + WTERMSIG(exec->status);
}

void	run_cmds(t_cmd *cmd, t_exe_pipe *exec, t_env **env)
{
	if (!exec->pid)
		child(cmd, env, exec);
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	close(exec->pipefd[1]);
	exec->prev_fd = exec->pipefd[0];
	if (cmd == exec->last_cmd)
		exec->last_pid = exec->pid;
	if (cmd->heredoc_fd > 0)
		close(cmd->heredoc_fd);
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
		x_pipe(exec.pipefd);
		exec.pid = fork();
		if (exec.pid < 0)
			return (perror("fork error"));
		run_cmds(cmd, &exec, env);
		cmd = cmd->next;
	}
	close_wait(env, &exec);
}
