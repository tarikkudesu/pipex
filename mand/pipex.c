/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/01 20:42:38 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child2_process(t_pipex *pipex)
{
	if (-1 == close(pipex->infile))
		(p_error(ERR_CLOSE), free_struct(pipex), exit(1));
	if (-1 == close(pipex->pipe_fd[WRITE_END]))
		(p_error(ERR_CLOSE), free_struct(pipex), exit(1));
	if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
		(p_error(ERR_DUP), free_struct(pipex), exit(1));
	if (-1 == dup2(pipex->pipe_fd[READ_END + 1], STDIN_FILENO))
		(p_error(ERR_DUP), free_struct(pipex), exit(1));
	if (check_cmd2(pipex))
		(free_struct(pipex), exit(1));
	execve(pipex->cmd2[0], pipex->cmd2, pipex->env);
	(p_error(ERR_EXECVE), free_struct(pipex), exit(1));
}

void	child1_process(t_pipex *pipex)
{
	if (-1 == close(pipex->outfile))
		(p_error(ERR_CLOSE), free_struct(pipex), exit(1));
	if (-1 == close(pipex->pipe_fd[READ_END]))
		(p_error(ERR_CLOSE), free_struct(pipex), exit(1));
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		(p_error(ERR_DUP), free_struct(pipex), exit(1));
	if (-1 == dup2(pipex->pipe_fd[WRITE_END], STDOUT_FILENO))
		(p_error(ERR_DUP), free_struct(pipex), exit(1));
	if (check_cmd1(pipex))
		(free_struct(pipex), exit(1));
	execve(pipex->cmd1[0], pipex->cmd1, pipex->env);
	(p_error(ERR_EXECVE), free_struct(pipex), exit(1));
}

void	close_fds(t_pipex *pipex)
{
	if (close(pipex->infile) == -1)
		(p_error(ERR_CLOSE), free_struct(pipex), exit(1));
	if (close(pipex->outfile) == -1)
		(p_error(ERR_CLOSE), free_struct(pipex), exit(1));
	if (close(pipex->pipe_fd[READ_END]) == -1)
		(p_error(ERR_CLOSE), free_struct(pipex), exit(1));
	if (close(pipex->pipe_fd[WRITE_END]) == -1)
		(p_error(ERR_CLOSE), free_struct(pipex), exit(1));
}

int	pipe_it(t_pipex *pipex)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex->pipe_fd) == -1)
		(p_error(ERR_PIPE), free_struct(pipex), exit(1));
	child1 = fork();
	if (-1 == child1)
		(p_error(ERR_FORK), free_struct(pipex), exit(1));
	if (0 == child1)
		child1_process(pipex);
	child2 = fork();
	if (-1 == child2)
		(p_error(ERR_FORK), free_struct(pipex), exit(1));
	if (0 == child2)
		child2_process(pipex);
	close_fds(pipex);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **environ)
{
	t_pipex	pipex;

	if (ac != 5)
		(print_error(ERR_ARG), exit(1));
	pipex.av = av;
	pipex.env = environ;
	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
	pipex.paths = NULL;
	if (parsing(&pipex))
		(free_struct(&pipex), exit(1));
	if (pipe_it(&pipex))
		(free_struct(&pipex), exit(1));
	free_struct(&pipex);
	exit(EXIT_SUCCESS);
}
