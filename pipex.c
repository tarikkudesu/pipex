/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/30 15:22:13 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child2_process(t_pipex *pipex)
{
	if (-1 == close(pipex->infile))
		return (p_error(ERR_CLOSE));
	if (-1 == close(pipex->pipe_fd[WRITE_END]))
		return (p_error(ERR_CLOSE));
	if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
		return (p_error(ERR_DUP));
	if (-1 == dup2(pipex->pipe_fd[READ_END], STDIN_FILENO))
		return (p_error(ERR_DUP));
	if (check_cmd2(pipex))
		return (1);
	execve(pipex->cmd2[0], pipex->cmd2, pipex->env);
	return (p_error(ERR_EXECVE));
}

int	child1_process(t_pipex *pipex)
{
	if (-1 == close(pipex->outfile))
		return (p_error(ERR_CLOSE));
	if (-1 == close(pipex->pipe_fd[READ_END]))
		return (p_error(ERR_CLOSE));
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		return (p_error(ERR_DUP));
	if (-1 == dup2(pipex->pipe_fd[WRITE_END], STDOUT_FILENO))
		return (p_error(ERR_DUP));
	if (check_cmd1(pipex))
		return (1);
	execve(pipex->cmd1[0], pipex->cmd1, pipex->env);
	return (p_error(ERR_EXECVE));
}

static int	close_fds(t_pipex pipex)
{
	if (close(pipex.infile) == -1)
		perror(ERR_CLOSE);
	if (close(pipex.outfile) == -1)
		perror(ERR_CLOSE);
	if (close(pipex.pipe_fd[READ_END]) == -1)
		perror(ERR_CLOSE);
	if (close(pipex.pipe_fd[WRITE_END]) == -1)
		perror(ERR_CLOSE);
	return (1);
}

int	pipe_it(t_pipex *pipex)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex->pipe_fd) == -1)
		return (p_error(ERR_PIPE));
	child1 = fork();
	if (-1 == child1)
		return (p_error(ERR_FORK));
	if (0 == child1)
		if (child1_process(pipex))
			return (1);
	child2 = fork();
	if (-1 == child2)
		return (p_error(ERR_FORK));
	if (0 == child2)
		if (child2_process(pipex))
			return (1);
	if (!close_fds(*pipex))
		return (1);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **environ)
{
	t_pipex	pipex;

	if (ac != 5)
		return (print_error(ERR_ARG), 1);
	pipex.av = av;
	pipex.env = environ;
	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
	pipex.paths = NULL;
	if (parsing(&pipex))
		return (free_struct(&pipex), 1);
	if (pipe_it(&pipex))
		return (free_struct(&pipex), 1);
	free_struct(&pipex);
}
