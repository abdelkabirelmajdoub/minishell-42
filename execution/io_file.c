/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:54:10 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/13 09:55:59 by ael-majd         ###   ########.fr       */
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
