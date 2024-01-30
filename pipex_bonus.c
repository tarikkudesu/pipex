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

void	free_struct_bonus(t_pip *pipex)
{
	int	i;

	i = -1;
	if (pipex->paths)
	{
		while (*(pipex->paths + ++i))
			free(*(pipex->paths + i));
		free(pipex->paths);
	}
	// i = -1;
	// if (pipex->pipes)
	// {
	// 	while (pipex->pipes[++i])
	// 		free(pipex->pipes[i]);
	// 	free(pipex->pipes);
	// }
	if (pipex->pid)
		free(pipex->pid);
}

static void	close_fds(t_pip *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_num - 1)
	{
		if (-1 == close(pipex->pipes[i][READ_END]))
			(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
		if (-1 == close(pipex->pipes[i][WRITE_END]))
			(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
	}
	if (-1 == close(pipex->infile))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
	if (-1 == close(pipex->outfile))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
}

void	execute(t_pip *pipex, char *cmd_string, int i)
{
	char	**cmd;

	if (i == 0)
		first_child(pipex);
	else if (i == pipex->cmd_num - 1)
		last_child(pipex);
	else
		middle_children(i - 1, pipex);
	cmd = cmd_check(cmd_string, pipex);
	if (!cmd)
		(free_struct_bonus(pipex), p_error(CMD_NOT_FOUND), exit(127));
	execve(cmd[0], cmd, pipex->environ);
	(free_struct_bonus(pipex), p_error(CMD_NOT_FOUND), exit(127));
}

void	pipex_mult_cmd(t_pip *pipex)
{
	int		i;

	i = -1;
	while (++i < pipex->cmd_num - 1)
		if (-1 == pipe(pipex->pipes[i]))
			(free_struct_bonus(pipex), p_error(ERR_PIPE), exit(1));
	i = -1;
	while (++i < pipex->cmd_num)
	{
		pipex->pid[i] = fork();
		if (-1 == pipex->pid[i])
			(free_struct_bonus(pipex), p_error(ERR_FORK), exit(1));
		if (pipex->pid[i] == 0)
			execute(pipex, pipex->argv[i + 2], i);
	}
	i = -1;
	while (++i < pipex->cmd_num)
	{
		printf("%d\n", pipex->pid[i]);
		// if (-1 == waitpid(pipex->pid[i], NULL, 0))
		// 	(free_struct_bonus(pipex), p_error(ERR_WAIT), exit(1));
	}
	close_fds(pipex);
}

int	pipex_here_doc(t_pip *pipex)
{
	(void)pipex;
	printf("This section is under Construction\n");
	return (1);
}

int	main(int ac, char **av, char **environ)
{
	t_pip	pipex;

	if (ac < 5)
		return (print_error(ERR_ARG), 1);
	pipex.argv = av;
	pipex.argc = ac;
	pipex.cmd_num = ac - 3;
	pipex.environ = environ;
	parsing(&pipex);
	if (0 == ft_strncmp(av[1], "here_doc", 8))
	{
		if (pipex_here_doc(&pipex))
			return (free_struct_bonus(&pipex), 1);
	}
	else
		pipex_mult_cmd(&pipex);
	free_struct_bonus(&pipex);
	exit(EXIT_SUCCESS);
}
