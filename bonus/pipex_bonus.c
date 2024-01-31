/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/31 17:12:26 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(char *cmd_string, t_pip *pipex)
{
	char	**cmd;
	char	*path;

	cmd = cmd_check(cmd_string, pipex);
	if (!cmd)
		(free_struct_bonus(pipex), exit(1));
	path = get_path(cmd[0], pipex->paths);
	if (!path)
		(free_array(cmd), free_struct_bonus(pipex), exit(1));
	execve(path, cmd, pipex->environ);
	(free(path), free_array(cmd), \
	free_struct_bonus(pipex), p_error(ERR_EXECVE), exit(1));
}

void	last_child(t_pip *pipex)
{
	int	pid;

	pid = fork();
	if (-1 == pid)
		(free_struct_bonus(pipex), p_error(ERR_FORK), exit(1));
	if (0 == pid)
	{
		if (-1 == close(pipex->infile))
			(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
		if (-1 == dup2(pipex->outfile, 1))
			(free_struct_bonus(pipex), p_error(ERR_DUP), exit(1));
		execute_cmd(pipex->argv[pipex->argc - 1], pipex);
	}
}

void	execute(t_pip *pipex, int i)
{
	char	*path;
	int		pid;

	if (-1 == pipe(pipex->fd))
		(free_struct_bonus(pipex), p_error(ERR_FORK), exit(1));
	pid = fork();
	if (-1 == pid)
		(free_struct_bonus(pipex), p_error(ERR_FORK), exit(1));
	if (0 == pid)
	{
		if (-1 == close(pipex->outfile)) 
			(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
		if (-1 == close(pipex->fd[READ_END]))
			(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
		if (-1 == dup2(pipex->fd[WRITE_END], 1))
			(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
		execute_cmd(pipex->argv[i + 2], pipex);
	}
}

void	pipex_mult_cmd(t_pip *pipex)
{
	int		i;

	if (-1 == dup2(pipex->infile, 0))
		(free_struct_bonus(pipex), p_error(ERR_DUP), exit(1));
	i = -1;
	while (++i < pipex->cmd_num - 1)
	{
		execute(pipex, i);
		if (-1 == close(pipex->fd[WRITE_END]))
			(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
		if (-1 == dup2(pipex->fd[0], 0))
			(free_struct_bonus(pipex), p_error(ERR_DUP), exit(1));
	}
	last_child(pipex);
	if (-1 == close(pipex->outfile))
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	i = 1;
	while (-1 != i)
		i = waitpid(-1, NULL, WNOHANG);
}

int	pipex_here_doc(t_pip *pipex)
{
	(void)pipex;
	printf("This section is under Construction\n");
	return (1);
}

void f(void) {system("lsof -c pipex_bonus");}

int	main(int ac, char **av, char **environ)
{
	t_pip	pipex;
	atexit(f);
	if (ac < 5)
		return (print_error(ERR_ARG), 1);
	pipex.argv = av;
	pipex.argc = ac;
	pipex.cmd_num = ac - 3;
	pipex.environ = environ;
	parsing(&pipex);
	if (0 == ft_strncmp(av[1], "here_doc", 8))
		pipex_here_doc(&pipex);
	else
		pipex_mult_cmd(&pipex);
	free_struct_bonus(&pipex);
}
