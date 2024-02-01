/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/01 15:37:57 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_pip *pipex)
{
	int	pid;

	pid = fork();
	if (-1 == pid)
		(free_struct_bonus(pipex), p_error(ERR_FORK), exit(1));
	if (0 == pid)
	{
		if (-1 == dup2(pipex->outfile, 1))
			(free_struct_bonus(pipex), p_error(ERR_DUP), exit(1));
		execute_cmd(pipex->argv[pipex->cmd_num - 1], pipex);
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
		if (-1 == close(pipex->fd[READ_END]))
			(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
		if (-1 == dup2(pipex->fd[WRITE_END], 1))
			(free_struct_bonus(pipex), p_error(ERR_DUP), exit(1));
		if (-1 == close(pipex->fd[WRITE_END]))
			(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
		execute_cmd(pipex->argv[i], pipex);
	}
}

void	mult_cmd(t_pip *pipex)
{
	int		i;

	if (-1 == dup2(pipex->infile, 0))
		(free_struct_bonus(pipex), p_error(ERR_DUP), exit(1));
	if (-1 == close(pipex->infile))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
	i = -1;
	while (++i < pipex->cmd_num - 1)
	{
		execute(pipex, i);
		if (-1 == close(pipex->fd[WRITE_END]))
			(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
		if (-1 == dup2(pipex->fd[READ_END], STDIN_FILENO))
			(free_struct_bonus(pipex), p_error(ERR_DUP), exit(1));
		if (-1 == close(pipex->fd[READ_END]))
			(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
	}
	last_child(pipex);
	if (-1 == close(STDIN_FILENO))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
	if (-1 == close(pipex->outfile))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
	i = 1;
	while (-1 != i)
		i = waitpid(-1, NULL, WNOHANG);
}

// void f(void) {system("lsof -c pipex_bonus");}

int	main(int ac, char **av, char **environ)
{
	t_pip	pipex;
	// atexit(f);
	if (ac < 5)
		return (print_error(ERR_ARG), 1);
	pipex.argv = av;
	pipex.argc = ac;
	pipex.cmd_num = ac - 3;
	pipex.environ = environ;
	if (0 == ft_strncmp(av[1], "here_doc", 8))
	{
		parsing(&pipex, 0);
		pipex_here_doc(&pipex);
	}
	else
	{
		parsing(&pipex, 1);
		pipex.argv = av + 2;
		mult_cmd(&pipex);
	}
	free_struct_bonus(&pipex);
}
// ./pipex file1 cmd1 cmd2 cmd3 file2
// ./pipex here_doc LIMITER cmd cmd1 file