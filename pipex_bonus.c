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

static int	close_fds(t_pipex *pipex, int fd[pipex->cmd_num - 1][2])
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

	pid = fork();
	if (-1 == pid)
		return (_error(ERR_FORK));
	if (0 == pid)
	{
		if (i == 0)
			if (first_child(pipex, fd))
				return (1);
		else if (i == pipex->cmd_num - 1)
			if (last_child(pipex, fd))
				return (1);
		else
			if (middle_children(i - 1, pipex, fd))
				return (1);
		cmd = cmd_check(cmd_string, pipex);
		if (!cmd)
			return (1);
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

int	pipex_here_doc(t_pipex *pipex)
{
	(void)pipex;
	printf("This section is under Construction\n");
	return 1;
}

int main(int ac, char **av, char **environ)
{
	t_pipex	pipex;

	if (ac < 5)
		return (print_error(ERR_ARG), 1);
	pipex.argv = av;
	pipex.argc = ac;
	pipex.cmd_num = ac - 3;
	pipex.environ = environ;
	if (parsing(&pipex))
		return (free_array(pipex.paths), 1);
	if (0 == ft_strncmp(av[1], "here_doc", 8))
	{
		if (pipex_here_doc(&pipex))
			return (free_array(pipex.paths), 1);
	}
	else
	{
		if (pipex_mult_cmd(&pipex))
			return (free_array(pipex.paths), 1);
	}
	free_array(pipex.paths);
	exit(EXIT_SUCCESS);
}
