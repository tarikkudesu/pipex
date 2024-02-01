/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:46 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/01 16:24:57 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child2_process(t_pip *pipex)
{
	if (-1 == close(pipex->infile))
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	if (-1 == close(pipex->fd[WRITE_END]))
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
		(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
	if (-1 == dup2(pipex->fd[READ_END], STDIN_FILENO))
		(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
	if (check_cmd2(pipex))
		(free_struct_bonus(pipex), exit(1));
	execve(pipex->cmd2[0], pipex->cmd2, pipex->environ);
	(p_error(ERR_EXECVE), free_struct_bonus(pipex), exit(1));
}

void	child1_process(t_pip *pipex)
{
	if (-1 == close(pipex->outfile))
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	if (-1 == close(pipex->fd[READ_END]))
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
	if (-1 == dup2(pipex->fd[WRITE_END], STDOUT_FILENO))
		(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
	if (check_cmd1(pipex))
		(free_struct_bonus(pipex), exit(1));
	execve(pipex->cmd1[0], pipex->cmd1, pipex->environ);
	(p_error(ERR_EXECVE), free_struct_bonus(pipex), exit(1));
}

void	close_fds(t_pip *pipex)
{
	if (close(pipex->infile) == -1)
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	if (close(pipex->outfile) == -1)
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	if (close(pipex->fd[READ_END]) == -1)
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	if (close(pipex->fd[WRITE_END]) == -1)
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
}

int	pipe_it(t_pip *pipex)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex->fd) == -1)
		(p_error(ERR_PIPE), free_struct_bonus(pipex), exit(1));
	child1 = fork();
	if (-1 == child1)
		(p_error(ERR_FORK), free_struct_bonus(pipex), exit(1));
	if (0 == child1)
		child1_process(pipex);
	child2 = fork();
	if (-1 == child2)
		(p_error(ERR_FORK), free_struct_bonus(pipex), exit(1));
	if (0 == child2)
		child2_process(pipex);
	close_fds(pipex);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}

void	here_doc(t_pip *pipex)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if ( -1 == fd)
		(free_struct_bonus(pipex), p_error(ERR_OPEN), exit(1));
	line = NULL;
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			(free_struct_bonus(pipex), p_error(ERR_GNL), exit(1));
		if (!ft_strncmp(line, pipex->argv[0], ft_strlen(pipex->argv[0])))
		{
			free(line);
			break ;
		}
		(ft_putstr_fd(line, fd), free(line));
	}
	if (-1 == close(fd))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
}
