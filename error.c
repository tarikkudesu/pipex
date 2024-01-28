/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:15:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/26 19:01:52 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	free_struct(t_pipex *pipex)
{
	char	**path;
	char	**cmd1;
	char	**cmd2;
	int		i;

	path = pipex->paths;
	cmd1 = pipex->cmd1;
	cmd2 = pipex->cmd2;
	i = -1;
	while (*(path + ++i))
		free(*(path + i));
	free(path);
	i = -1;
	while (*(cmd1 + ++i))
		free(*(cmd1 + i));
	free(cmd1);
	i = -1;
	while (*(cmd2 + ++i))
		free(*(cmd2 + i));
	free(cmd2);
}

void	_exit_pipex(t_pipex *pipex, int err)
{
	free_struct(pipex);
	exit(err);
}

void	*_error_(char *s)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	perror(s);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	return (NULL);
}

int	_error(char *s)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	perror(s);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	return (1);
}

void	done(void)
{
	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd(LINE_, STDOUT_FILENO);
	ft_putstr_fd(COMPILED, STDOUT_FILENO);
	ft_putstr_fd(LINE_, STDOUT_FILENO);
	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
}
