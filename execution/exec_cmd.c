/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:35:03 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/15 16:21:52 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	child_proc(t_cmd *cmd, char **envp)
{
	char	*path;

	if (cmd->limiter)
		x_dup2(cmd->heredoc_fd, STDIN_FILENO);
	else if (cmd->infile)
		redirect_in(cmd->infile);
	if (cmd->out_file)
		redirect_out(cmd);
	path = get_path(cmd->args[0], envp);
	execve(path, cmd->args, envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(path);
	exit(127);
}
void	cmd_builtin(t_cmd *cmd, t_env **env, int *status)
{
	int	in_save;
	int	out_save;

	in_save = dup(STDIN_FILENO);
	out_save = dup(STDOUT_FILENO);
	if (cmd->limiter)
		x_dup2(cmd->heredoc_fd, STDIN_FILENO);
	else if (cmd->infile)
		redirect_in(cmd->infile);
	if (cmd->out_file)
		redirect_out(cmd);
	*status = run_builtin(cmd, env);
	(*env)->exit_status = *status;
	x_dup2(in_save, STDIN_FILENO);
	x_dup2(out_save, STDOUT_FILENO);
	close(in_save);
	close(out_save);
}

void	execute_one(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	char	**envp;
	int		status;
	
	if (!cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
		return cmd_builtin(cmd, env, &status);
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

void exe(t_cmd  *cmd_list, t_env **env)
{
	prepare_heredocs(cmd_list, env);
	if (is_pipe(cmd_list))
		execute_pipe(cmd_list, env);
	else
		execute_one(cmd_list, env);
}
