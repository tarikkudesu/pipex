/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:46 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 14:57:43 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	second_child(t_pip *pipex)
{
	pipex->outfile = open(pipex->argv[5], \
	O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfile == -1)
		(free_struct_bonus(pipex), perror(ERR_OPEN), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->fd[READ_END], 0))
		(free_struct_bonus(pipex), perror(ERR_DUP), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[READ_END]))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->outfile, 1))
		(free_struct_bonus(pipex), perror(ERR_DUP), exit(EXIT_FAILURE));
	if (-1 == close(pipex->outfile))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[WRITE_END]))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	execute_cmd(pipex->argv[4], pipex);
}

void	first_child(t_pip *pipex)
{
	pipex->infile = open(".tmp", O_RDONLY);
	if (pipex->infile == -1)
		(free_struct_bonus(pipex), perror(ERR_OPEN), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == close(pipex->infile))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->fd[WRITE_END], STDOUT_FILENO))
		(free_struct_bonus(pipex), perror(ERR_DUP), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[WRITE_END]))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[READ_END]))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	execute_cmd(pipex->argv[3], pipex);
}

void	execute_here_doc(t_pip *pipex)
{
	char	*path;

	if (-1 == pipe(pipex->fd))
		(free_struct_bonus(pipex), perror(ERR_PIPE), exit(EXIT_FAILURE));
	pipex->pids[0] = fork();
	if (-1 == pipex->pids[0])
		(free_struct_bonus(pipex), perror(ERR_FORK), exit(EXIT_FAILURE));
	if (0 == pipex->pids[0])
		first_child(pipex);
	pipex->pids[1] = fork();
	if (-1 == pipex->pids[1])
		(free_struct_bonus(pipex), perror(ERR_FORK), exit(EXIT_FAILURE));
	if (0 == pipex->pids[1])
		second_child(pipex);
	if (-1 == close(pipex->fd[READ_END]))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
	if (-1 == close(pipex->fd[WRITE_END]))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
}

void	pipe_it(t_pip *pipex)
{
	int		i;
	int		status;

	i = 0;
	execute_here_doc(pipex);
	waitpid(pipex->pids[1], &status, 0);
	exit_status(WEXITSTATUS(status), &i);
	waitpid(pipex->pids[0], &status, 0);
	exit_status(WEXITSTATUS(status), &i);
	if (-1 == unlink(".tmp"))
		(free_struct_bonus(pipex), perror(ERR_UNLINK), exit(EXIT_FAILURE));
	if (i == 2)
		(free_struct_bonus(pipex), exit(EXIT_SUCCESS));
}
