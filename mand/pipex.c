/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/03 11:23:32 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_child(t_pip *pipex)
{
	pipex->outfile = open(pipex->argv[pipex->argc - 1], \
	O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfile == -1)
		(free_struct(pipex), perror(ERR_OPEN), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->fd[READ_END], STDIN_FILENO))
		(free_struct(pipex), perror(ERR_DUP), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[READ_END]))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
		(free_struct(pipex), perror(ERR_DUP), exit(EXIT_FAILURE));
	if (-1 == close(pipex->outfile))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[WRITE_END]))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	execute_cmd(pipex->argv[pipex->argc - 2], pipex);
}

void	first_child(t_pip *pipex)
{
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
		(free_struct(pipex), perror(ERR_OPEN), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == close(pipex->infile))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->fd[WRITE_END], STDOUT_FILENO))
		(free_struct(pipex), perror(ERR_DUP), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[WRITE_END]))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[READ_END]))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	execute_cmd(pipex->argv[pipex->argc - 3], pipex);
}

void	execute(t_pip *pipex)
{
	char	*path;

	if (-1 == pipe(pipex->fd))
		(free_struct(pipex), perror(ERR_PIPE), exit(EXIT_FAILURE));
	pipex->pids[0] = fork();
	if (-1 == pipex->pids[0])
		(free_struct(pipex), perror(ERR_FORK), exit(EXIT_FAILURE));
	if (0 == pipex->pids[0])
		first_child(pipex);
	pipex->pids[1] = fork();
	if (-1 == pipex->pids[1])
		(free_struct(pipex), perror(ERR_FORK), exit(EXIT_FAILURE));
	if (0 == pipex->pids[1])
		second_child(pipex);
	if (-1 == close(pipex->fd[READ_END]))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[WRITE_END]))
		(free_struct(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
}

void	pipe_it(t_pip *pipex)
{
	int		i;
	int		status;

	i = 0;
	execute(pipex);
	waitpid(pipex->pids[1], &status, 0);
	exit_status(WEXITSTATUS(status), &i);
	waitpid(pipex->pids[0], &status, 0);
	exit_status(WEXITSTATUS(status), &i);
	if (i == 2)
		(free_struct(pipex), exit(EXIT_SUCCESS));
}

void f(void) {system("lsof -c pipex");}

int	main(int ac, char **av, char **environ)
{
	t_pip	pipex;

	atexit(f);
	if (ac != 5)
		return (ft_putstr_fd(ERR_ARG, 2), 1);
	pipex.argc = ac;
	pipex.argv = av;
	pipex.pids = NULL;
	pipex.environ = environ;
	parsing(&pipex);
	pipe_it(&pipex);
	(free_struct(&pipex), exit(EXIT_FAILURE));
}
