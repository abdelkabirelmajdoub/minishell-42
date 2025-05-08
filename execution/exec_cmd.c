/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:35:03 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/08 12:58:16 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		if (cmd->args)
		{
			for (i = 0; cmd->args[i]; i++)
				free(cmd->args[i]);
			free(cmd->args);
		}
		free(cmd->infile);
		free(cmd->out_file);
		free(cmd->append);
		free(cmd->limiter);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

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
	char	*path;
	int		status;
	
	if (is_builtin(cmd->args[0]))
	{
		status = run_builtin(cmd, env);
		(*env)->exit_status = status;
		return;
	}
	pid = fork();
	if (!pid)
	{
		if (cmd->limiter)
			dup2(cmd->heredoc_fd, STDIN_FILENO);
		else if (cmd->infile)
			redirect_in(cmd->infile);
		if (cmd->out_file)
			redirect_out(cmd->out_file, cmd->append);
		path = get_path(cmd->args[0], v_tmp);
		execve(path, cmd->args, v_tmp);
		printf("minishell: %s: command not found\n", cmd->args[0]);
		free(path);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*env)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*env)->exit_status = 128 + WTERMSIG(status);
}

void	execute_pipe(t_cmd *cmd, t_env **env, char **v_tmp)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	char	*path;
	int		status;

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
			path = get_path(cmd->args[0], v_tmp);
			if (is_builtin(cmd->args[0]))
				exit(run_builtin(cmd, env));
			else
				execve(path, cmd->args, v_tmp);
			printf("minishell: %s: command not found\n", cmd->args[0]);
			free(path);
			exit(1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		close(pipefd[1]);
		prev_fd = pipefd[0];
		close(pipefd[0]);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		(*env)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*env)->exit_status = 128 + WTERMSIG(status);
}

int	is_pipe(t_cmd *cmd_list)
{
	return (cmd_list && cmd_list->next);
}

void exe(t_cmd  *cmd_list, char **v_tmp, t_env **env)
{
	prepare_heredocs(cmd_list);
	if (is_pipe(cmd_list))
		execute_pipe(cmd_list, env, v_tmp);
	else
		execute_one(cmd_list, env, v_tmp);
}
