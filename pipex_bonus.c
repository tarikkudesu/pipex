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

void	print_arr(char **arr)
{
	int i = -1;
	while (*(arr + ++i))
		printf("%s\n", *(arr + i));
}
static int	close_fds(t_pipex *pipex, int fd[pipex->cmd_num][2])
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_num)
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

void	execute(t_pipex *pipex, char *cmd_string, int i, int fd[pipex->cmd_num - 1][2])
{
	int		pid;
	char	**cmd;

	pid = fork();
	if (-1 == pid)
		_error(ERR_FORK);
	if (0 == pid)
	{
		if (i == 0)
			first_child(pipex, fd);
		if (i == pipex->cmd_num - 1)
			last_child(pipex, fd);
		else
			middle_children(i - 1, pipex, fd);
		cmd = cmd_check(cmd_string, pipex);
		execve(cmd[0], cmd, pipex->environ);
		_error(ERR_EXECVE);
	}
}

int	pipex_mult_cmd(t_pipex *pipex)
{
	int		i;
	int		fd[pipex->cmd_num - 1][2];

	print_arr(pipex->paths);
	printf("%d\t%d\n", pipex->infile, pipex->outfile);
	i = -1;
	while (++i < pipex->cmd_num - 1)
		if (-1 == pipe(fd[i]))
			return (_error(ERR_PIPE));
	i = -1;
	while (++i < pipex->cmd_num)
		execute(pipex, pipex->argv[i + 2], i, fd);
	if (close_fds(pipex, fd))
		return (1);
	return (0);
}

void	pipex_here_doc(t_pipex *pipex)
{
	(void)pipex;
	printf("This section is under Construction");
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
	pipex.environ = environ;
	pipex.cmd_num = ac - 3;
	if (parsing(&pipex))
		_exit_pipex(&pipex, 1);
	if (0 == ft_strncmp(av[1], "here_doc", 8))
		pipex_here_doc(&pipex);
	else
		pipex_mult_cmd(&pipex);
	free_struct(&pipex);
	exit(EXIT_SUCCESS);
}