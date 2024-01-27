/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/26 19:00:44 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	*child1_process(t_pipex **pipex)
{
	close((*pipex)->outfile);
	close((*pipex)->pipe_fd[READ_END]);
	if (-1 == dup2((*pipex)->infile, STDIN_FILENO))
		return (_error_(ERR_DUP));
	if (-1 == dup2((*pipex)->pipe_fd[WRITE_END], STDOUT_FILENO))
		return (_error_(ERR_DUP));
	close((*pipex)->infile);
	close((*pipex)->pipe_fd[WRITE_END]);
	execve((*pipex)->cmd1[0], (*pipex)->cmd1, (*pipex)->env);
	return (_error_(ERR_EXECVE));
}

void	*child2_process(t_pipex **pipex)
{
	close(((*pipex))->pipe_fd[WRITE_END]);
	close((*pipex)->infile);
	if (-1 == dup2((*pipex)->outfile, STDOUT_FILENO))
		return (_error_(ERR_DUP));
	if (-1 == dup2((*pipex)->pipe_fd[READ_END], STDIN_FILENO))
		return (_error_(ERR_DUP));
	close((*pipex)->outfile);
	close((*pipex)->pipe_fd[READ_END]);
	execve((*pipex)->cmd2[0], (*pipex)->cmd2, (*pipex)->env);
	return (_error_(ERR_EXECVE));
}

int	pipe_it(t_pipex **pipex)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe((*pipex)->pipe_fd) == -1)
		return (_error(ERR_PIPE));
	child1 = fork();
	if (-1 == child1)
		return (_error(ERR_FORK));
	if (0 == child1)
		if (!child1_process(pipex))
			return (1);
	child2 = fork();
	if (-1 == child2)
		return (_error(ERR_FORK));
	if (0 == child2)
		if (!child2_process(pipex))
			return (1);
	if (close((*pipex)->infile) < 0)
		perror(strerror(errno));
	close((*pipex)->outfile);
	close((*pipex)->pipe_fd[READ_END]);
	close((*pipex)->pipe_fd[WRITE_END]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}

void	_exit_pipex(t_pipex **pipex, int err)
{
	if ((*pipex)->cmd1)
		ft_error((*pipex)->cmd1);
	if ((*pipex)->cmd2)
		ft_error((*pipex)->cmd1);
	if (pipex)
		free(*pipex);
	exit(err);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	if (ac != 5)
	{
		_error(ERR_ARG);
		_exit_pipex(NULL, 1);
	}
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
	{
		_error(ERR_MAL);
		_exit_pipex(&pipex, 1);
	}
	pipex->av = av;
	pipex->env = env;
	if (parcing(pipex))
		_exit_pipex(&pipex, 2);
	if (pipe_it(&pipex))
		_exit_pipex(&pipex, 2);
	done();
	_exit_pipex(&pipex, 0);
}
