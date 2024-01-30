/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/30 15:29:22 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	close_fds(t_pipex *pipex, int fd[pipex->cmd_num - 1][2])
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_num - 1)
	{
		if (-1 == close(fd[i][READ_END]))
			return (_error(ERR_CLOSE));
		if (-1 == close(fd[i][WRITE_END]))
			return (_error(ERR_CLOSE));
	}
	if (-1 == close(pipex->infile))
		return (_error(ERR_CLOSE));
	if (-1 == close(pipex->outfile))
		return (_error(ERR_CLOSE));
	return (0);
}

int	execute(t_pipex *pipex, char *cmd_string, int i, \
int fd[pipex->cmd_num - 1][2])
{
	char	**cmd;

	if (i == 0)
		first_child(pipex, fd);
	else if (i == pipex->cmd_num - 1)
		last_child(pipex, fd);
	else
		middle_children(i - 1, pipex, fd);
	cmd = cmd_check(cmd_string, pipex);
	if (!cmd)
		return (1);
	execve(cmd[0], cmd, pipex->environ);
	(_error(ERR_EXECVE), free_array(pipex->paths), exit(127));
	return (0);
}

int	pipex_mult_cmd(t_pipex *pipex)
{
	int		i;
	int		pid[pipex->cmd_num];
	int		fd[pipex->cmd_num - 1][2];

	i = -1;
	while (++i < pipex->cmd_num - 1)
		if (-1 == pipe(fd[i]))
			return (_error(ERR_PIPE));
	i = -1;
	while (++i < pipex->cmd_num)
	{
		pid[i] = fork();
		if (-1 == pid[i])
			return (_error(ERR_FORK));
		if (pid[i] == 0)
			if (execute(pipex, pipex->argv[i + 2], i, fd))
				return (1);
	}
	i = -1;
	while (i < pipex->cmd_num)
		if (-1 == waitpid(pid[i], NULL, 0))
			return (_error(ERR_WAIT));
	if (close_fds(pipex, fd))
		return (_error(ERR_CLOSE));
	return (0);
}

int	pipex_here_doc(t_pipex *pipex)
{
	(void)pipex;
	printf("This section is under Construction\n");
	return (1);
}

int	main(int ac, char **av, char **environ)
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
