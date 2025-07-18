/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:35:03 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/25 09:29:04 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_proc(t_cmd *cmd, char **envp)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->limiter)
		x_dup2(cmd->heredoc_fd, STDIN_FILENO);
	else if (cmd->infile)
		redirect_in(cmd->infile);
	if (cmd->out_file)
		redirect_out(cmd);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	path = get_path(cmd->args[0], envp);
	execve(path, cmd->args, envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(path);
	exit(127);
}

int	exist_infile(char *filename, t_env **env)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0777);
	if (fd < 0)
	{
		perror("infile error");
		(*env)->exit_status = 1;
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return ((*env)->exit_status = 1, 0);
	close(fd);
	return (1);
}

void	cmd_builtin(t_cmd *cmd, t_env **env, int *status)
{
	int	in_save;
	int	out_save;

	in_save = dup(STDIN_FILENO);
	out_save = dup(STDOUT_FILENO);
	if (cmd->limiter)
		x_dup2(cmd->heredoc_fd, STDIN_FILENO);
	else if (cmd->infile && !exist_infile(cmd->infile, env))
	{
		close(in_save);
		close(out_save);
		return ;
	}
	if (cmd->out_file && !out_exist(cmd, env))
	{
		close(in_save);
		close(out_save);
		return ;
	}
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

	if (is_builtin(cmd->args[0]))
		return (cmd_builtin(cmd, env, &status));
	envp = env_list_to_array(env);
	pid = fork();
	if (!pid)
		child_proc(cmd, envp);
	free_args(envp);
	close(cmd->heredoc_fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*env)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		(*env)->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	exe(t_cmd *cmd_list, t_env **env)
{
	if (prepare_heredocs(cmd_list, env))
		return ;
	set_signals();
	if (cmd_list && cmd_list->next)
		execute_pipe(cmd_list, env);
	else
		execute_one(cmd_list, env);
}
