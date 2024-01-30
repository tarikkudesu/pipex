/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:15:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/30 15:09:53 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_struct_bonus(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->paths)
	{
		while (*(pipex->paths + ++i))
			free(*(pipex->paths + i));
		free(pipex->paths);
	}
	i = -1
	if (pipex->pipes)
	{
		while (*(pipex->pipes + ++i))
			free(*(pipex->pipes + i));
		free(pipex->pipes);
	}
	if (pipex->pid)
		free(pipex->pid);
}

int	p_error(char *s)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	perror(s);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	return (1);
}

void	print_error(char *s)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}
