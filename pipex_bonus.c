/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/31 12:09:28 by tamehri          ###   ########.fr       */
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
}

static void	close_fds(t_pip *pipex)
{
	if (-1 == close(pipex->infile))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
	if (-1 == close(pipex->outfile))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
}

char	*get_path(char *cmd, char **path)
{
	char	*temp;
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (print_error(ERR_MAL), NULL);
	while (*(path + ++i))
	{
		temp = ft_strjoin(*(path + i), tmp);
		if (!temp)
			return (free(tmp), print_error(ERR_MAL), NULL);
		if (!access(temp, F_OK | X_OK))
			return (free(tmp), temp);
		free(temp);
	}
	free(tmp);
	return (NULL);
}


void	execute(t_pip *pipex, int fd[2], char **cmd, int i)
{
	char	*path;
	int		pid;

	pid = fork();
	if (-1 == pid)
		(free_array(cmd), free_struct_bonus(pipex), \
		p_error(ERR_FORK), exit(1));
	path = get_path(cmd[0], pipex->paths);
	if (!path)
		(free_array(cmd), free_struct_bonus(pipex), \
		p_error(ERR_FORK), exit(1));
	if (0 == pid)
	{
		if (i == pipex->cmd_num - 1)
			last_process(pipex, fd);
		else
			processes(pipex, fd);
		execve(path, cmd, pipex->environ);
		(free(path), free_array(cmd), \
		free_struct_bonus(pipex), p_error(ERR_EXECVE), exit(127));
	}
}

void	pipex_mult_cmd(t_pip *pipex)
{
	int		fd[2];
	char	**cmd;
	int		i;

	i = -1;
	while (++i < pipex->cmd_num)
	{
		if (-1 == pipe(fd))
		{
			p_error(ERR_PIPE);
			break ;
		}
		cmd = cmd_check(pipex->argv[i + 2], pipex);
		if (!cmd)
			break ;
		// if (-1 == dup2(pipex->infile, fd[0]))
		// {
		// 	p_error(ERR_DUP);
		// 	break ;
		// }
		execute(pipex, fd, cmd, i);
	}
	// i = 1;
	// while (i)
	// 	i = waitpid(-1, NULL, WNOHANG);
	// close_fds(pipex);
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
}
