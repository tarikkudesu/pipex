/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/29 13:16:22 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	close_fds(t_pipex *pipex, int fd[pipex->cmd_num][2])
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_num - 1)
	{
		if (-1 == close(fd[i][0]))
			return (_error(ERR_CLOSE));
		if (-1 == close(fd[i][1]))
			return (_error(ERR_CLOSE));
	}
	if (-1 == close(pipex->infile))
		return (_error(ERR_CLOSE));
	if (-1 == close(pipex->outfile))
		return (_error(ERR_CLOSE));
	return (0);
}

int	execute(t_pipex *pipex, char *cmd_string, int i, int fd[pipex->cmd_num - 1][2])
{
	int		pid;
	char	**cmd;

	(void)fd;
	pid = fork();
	if (-1 == pid)
		return (_error(ERR_FORK));
	if (0 == pid)
	{
		if (i == 0)
			first_child(pipex, fd);
		else if (i == pipex->cmd_num - 1)
			last_child(pipex, fd);
		else
			middle_children(i - 1, pipex, fd);
		cmd = cmd_check(cmd_string, pipex);
		execve(cmd[0], cmd, pipex->environ);
		return (_error(ERR_EXECVE));
	}
	return (0);
}

int	pipex_mult_cmd(t_pipex *pipex)
{
	int		i;
	int		fd[pipex->cmd_num - 1][2];

	i = -1;
	while (++i < pipex->cmd_num - 1)
		if (-1 == pipe(fd[i]))
			return (_error(ERR_PIPE));
	if (close_fds(pipex, fd))
		return (_error(ERR_CLOSE));
	i = -1;
	while (++i < pipex->cmd_num)
		if (execute(pipex, pipex->argv[i + 2], i, fd))
			return (1);
	return (0);
}

void	pipex_here_doc(t_pipex *pipex)
{
	(void)pipex;
	printf("This section is under Construction\n");
}

int main(int ac, char **av, char **environ)
{
	t_pipex	pipex;

	if (ac < 5)
	{
		_error(ERR_ARG);
		exit(1);
	}
	pipex.argv = av;
	pipex.argc = ac;
	pipex.cmd_num = ac - 3;
	pipex.environ = environ;
	if (parsing(&pipex))
	{
		free_struct_bonus(&pipex);
		exit(1);
	}
	if (0 == ft_strncmp(av[1], "here_doc", 8))
		pipex_here_doc(&pipex);
	else
		pipex_mult_cmd(&pipex);
	exit(EXIT_SUCCESS);
}