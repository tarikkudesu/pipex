/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:19:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/04 18:40:19 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_process(t_pip *pipex)
{
	pipex->pids[pipex->cmd_num - 1] = fork();
	if (-1 == pipex->pids[pipex->cmd_num - 1])
		(free_struct_bonus(pipex), perror(ERR_FORK), exit(EXIT_FAILURE));
	if (0 == pipex->pids[pipex->cmd_num - 1])
	{
		if (pipex->here_doc)
			pipex->outfile = open(pipex->outfilename, \
			O_WRONLY | O_APPEND | O_CREAT, 0777);
		else
			pipex->outfile = open(pipex->outfilename, \
			O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (pipex->outfile == -1)
			(free_struct_bonus(pipex), perror(ERR_OPEN), exit(EXIT_FAILURE));
		if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
			(close(pipex->outfile), free_struct_bonus(pipex), \
			perror(ERR_DUP), exit(EXIT_FAILURE));
		execute_cmd(pipex->argv[pipex->cmd_num - 1], pipex);
	}
	close(STDIN_FILENO);
}

void	first_process(t_pip *pipex)
{
	pipex->infile = open(pipex->infilename, O_RDONLY);
	if (pipex->infile == -1)
		(close(pipex->fd[READ_END]), close(pipex->fd[WRITE_END]), \
		free_struct_bonus(pipex), perror(ERR_OPEN), exit(EXIT_FAILURE));
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		(close(pipex->fd[READ_END]), close(pipex->fd[WRITE_END]), \
		free_struct_bonus(pipex), perror(ERR_CLOSE), \
		close(pipex->infile), exit(EXIT_FAILURE));
	close(pipex->infile);
	if (-1 == dup2(pipex->fd[WRITE_END], STDOUT_FILENO))
		(close(pipex->fd[READ_END]), close(pipex->fd[WRITE_END]), \
		free_struct_bonus(pipex), perror(ERR_DUP), \
		close(pipex->infile), exit(EXIT_FAILURE));
	execute_cmd(pipex->argv[0], pipex);
}

void	execute(t_pip *pipex, int i)
{
	char	*path;

	if (-1 == pipe(pipex->fd))
		(free_struct_bonus(pipex), perror(ERR_PIPE), exit(EXIT_FAILURE));
	pipex->pids[i] = fork();
	if (-1 == pipex->pids[i])
		(close(pipex->fd[READ_END]), close(pipex->fd[WRITE_END]), \
		free_struct_bonus(pipex), perror(ERR_FORK), exit(EXIT_FAILURE));
	if (0 == i && 0 == pipex->pids[i])
		first_process(pipex);
	else if (0 == pipex->pids[i])
	{
		close(pipex->fd[READ_END]);
		if (-1 == dup2(pipex->fd[WRITE_END], STDOUT_FILENO))
			(close(pipex->fd[WRITE_END]), free_struct_bonus(pipex), \
			perror(ERR_FORK), exit(EXIT_FAILURE));
		close(pipex->fd[WRITE_END]);
		execute_cmd(pipex->argv[i], pipex);
	}
	close(pipex->fd[WRITE_END]);
	if (-1 == dup2(pipex->fd[READ_END], STDIN_FILENO))
		(close(pipex->fd[READ_END]), free_struct_bonus(pipex), \
		perror(ERR_DUP), exit(EXIT_FAILURE));
	close(pipex->fd[READ_END]);
}

void	pipex_mult_cmd(t_pip *pipex)
{
	int		i;
	int		j;
	int		status;

	i = -1;
	while (++i < pipex->cmd_num - 1)
		execute(pipex, i);
	last_process(pipex);
	j = 0;
	i = -1;
	while (++i < pipex->cmd_num)
	{
		waitpid(pipex->pids[i], &status, 0);
		exit_status(WEXITSTATUS(status), &j);
	}
	if (pipex->here_doc)
		if (-1 == unlink(pipex->infilename))
			(free_struct_bonus(pipex), perror(ERR_UNLINK), exit(EXIT_FAILURE));
	if (j == pipex->cmd_num - 1)
		(free_struct_bonus(pipex), exit(EXIT_SUCCESS));
}
