/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 11:07:04 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_pip *pipex)
{
	int	pid;

	pid = fork();
	if (-1 == pid)
		(free_struct_bonus(pipex), p_error(ERR_FORK), exit(1));
	pipex->pid[pipex->cmd_num - 1] = pid;
	if (0 == pid)
	{
		pipex->outfile = open(pipex->argv[pipex->argc - 1], \
		O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (pipex->outfile == -1)
			(free_struct_bonus(pipex), perror(ERR_OPEN), exit(1));
		if (-1 == dup2(pipex->outfile, 1))
			(free_struct_bonus(pipex), perror(ERR_DUP), exit(1));
		execute_cmd(pipex->argv[pipex->argc - 2], pipex);
	}
	if (-1 == close(STDIN_FILENO))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(1));
}

void	first_child(t_pip *pipex)
{
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
		(free_struct_bonus(pipex), perror(ERR_OPEN), exit(1));
	if (-1 == dup2(pipex->infile, 0))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(1));
	if (-1 == close(pipex->infile))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(1));
	if (-1 == dup2(pipex->fd[WRITE_END], 1))
		(free_struct_bonus(pipex), perror(ERR_DUP), exit(1));
	execute_cmd(pipex->argv[pipex->cmd_num - 1], pipex);
}

void	execute(t_pip *pipex, int i)
{
	char	*path;

	if (-1 == pipe(pipex->fd))
		(free_struct_bonus(pipex), perror(ERR_FORK), exit(1));
	pipex->pid[i] = fork();
	if (-1 == pipex->pid[i])
		(free_struct_bonus(pipex), perror(ERR_FORK), exit(1));
	if (0 == i && 0 == pipex->pid[i])
		first_child(pipex);
	else if (0 == pipex->pid[i])
	{
		if (-1 == close(pipex->fd[READ_END]))
			(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(1));
		if (-1 == dup2(pipex->fd[WRITE_END], 1))
			(free_struct_bonus(pipex), perror(ERR_FORK), exit(1));
		if (-1 == close(pipex->fd[WRITE_END]))
			(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(1));
		execute_cmd(pipex->argv[i + 2], pipex);
	}
}

void	exit_pipex(int exit_code, int *j)
{
	if (0 == exit_code)
		(*j)++;
}

void	pipex_mult_cmd(t_pip *pipex)
{
	int		i;
	int		j;
	int		status;

	i = -1;
	while (++i < pipex->cmd_num - 1)
	{
		execute(pipex, i);
		if (-1 == close(pipex->fd[WRITE_END]))
			(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(1));
		if (-1 == dup2(pipex->fd[READ_END], STDIN_FILENO))
			(free_struct_bonus(pipex), perror(ERR_DUP), exit(1));
		if (-1 == close(pipex->fd[READ_END]))
			(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(1));
	}
	last_child(pipex);
	i = -1;
	j = 0;
	while (++i < pipex->cmd_num)
	{
		waitpid(pipex->pid[i], &status, 0);
		exit_pipex(WEXITSTATUS(status), &j);
		if (j == pipex->cmd_num - 1)
			(free_struct_bonus(pipex), exit(EXIT_SUCCESS));
	}
}

void	pipex_here_doc(t_pip *pipex)
{
	int	infile;

	here_doc(pipex);
	infile = open(".tmp", O_RDONLY);
	if (-1 == infile)
		(free_struct_bonus(pipex), p_error(ERR_OPEN), exit(1));
	pipex->infile = infile;
	pipe_it(pipex);
	if (-1 == unlink(".tmp"))
		(free_struct_bonus(pipex), p_error(ERR_UNLINK), exit(1));
}

int	main(int ac, char **av, char **environ)
{
	t_pip	pipex;

	if (ac < 5)
		return (print_error(ERR_ARG), 1);
	pipex.argc = ac;
	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
	pipex.pid = NULL;
	pipex.argv = av;
	pipex.cmd_num = ac - 3;
	pipex.environ = environ;
	if (0 == ft_strncmp(av[1], "here_doc", 8))
	{
		if (ac != 6)
			return (print_error(ERR_ARG), 1);
		parsing_here_doc(&pipex);
		pipex_here_doc(&pipex);
	}
	else
	{
		parsing(&pipex);
		pipex_mult_cmd(&pipex);
	}
	(free_struct_bonus(&pipex), exit(EXIT_FAILURE));
}
