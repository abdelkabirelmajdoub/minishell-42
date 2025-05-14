/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:54:10 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/13 14:51:43 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	x_dup2(int fd, int target_fd)
{
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2 error");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	x_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
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
	x_dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_out(t_cmd	*cmd)
{
	int	i;
	int	fd;

	i = -1;
	while(cmd->out_file[++i])
	{
		if (cmd->append)
			fd = open(cmd->out_file[i], O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fd = open(cmd->out_file[i], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
		{
			perror("outfile error");
			exit(1);
		}
		if (cmd->out_file[i + 1] == NULL)
			x_dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
