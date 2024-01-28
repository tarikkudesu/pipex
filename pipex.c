/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/28 20:34:41 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*child2_process(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->pipe_fd[WRITE_END]);
	if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
		return (_error_(ERR_DUP));
	if (-1 == dup2(pipex->pipe_fd[READ_END], STDIN_FILENO))
		return (_error_(ERR_DUP));
	if (check_cmd2(pipex))
		return (NULL);
	execve(pipex->cmd2[0], pipex->cmd2, pipex->env);
	return (_error_(ERR_EXECVE));
}

void	*child1_process(t_pipex *pipex)
{
	close(pipex->outfile);
	close(pipex->pipe_fd[READ_END]);
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		return (_error_(ERR_DUP));
	if (-1 == dup2(pipex->pipe_fd[WRITE_END], STDOUT_FILENO))
		return (_error_(ERR_DUP));
	if (check_cmd1(pipex))
		return (NULL);
	execve(pipex->cmd1[0], pipex->cmd1, pipex->env);
	return (_error_(ERR_EXECVE));
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
	pid_t	status1;
	pid_t	status2;

	if (pipe(pipex->pipe_fd) == -1)
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
	if (!close_fds(*pipex))
		return (1);
	waitpid(child1, &status1, 0);
	waitpid(child2, &status2, 0);
	return (0);
}
// void f(void) {system("lsof -c pipex");}

int	main(int ac, char **av, char **environ)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		_error(ERR_ARG);
		exit(1);
	}
	// atexit(f);
	pipex.av = av;
	pipex.env = environ;
	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
	pipex.paths = NULL;
	if (parsing(&pipex))
		_exit_pipex(&pipex, 2);
	if (pipe_it(&pipex))
		_exit_pipex(&pipex, 2);
	free_struct(&pipex);
}
