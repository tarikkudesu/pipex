/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:57 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/30 13:40:09 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	first_child(t_pipex *pipex, int fd[pipex->cmd_num - 1][2])
{
	int	j;

	j = -1;
	while (++j < pipex->cmd_num - 1)
	{
		if (-1 == close(fd[j][READ_END]))
			(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
		if (j != 0)
			if (-1 == close(fd[j][READ_END]))
				(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	}
	if (-1 == close(pipex->outfile))
		(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	if (-1 == dup2(fd[0][WRITE_END], STDOUT_FILENO))
		(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	return (0);
}

int	last_child(t_pipex *pipex, int fd[pipex->cmd_num - 1][2])
{
	int	j;

	j = -1;
	while (++j < pipex->cmd_num - 1)
	{
		if (-1 == close(fd[j][WRITE_END]))
			(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
		if (j != pipex->cmd_num - 2)
			if (-1 == close(fd[j][READ_END]))
				(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	}
	if (-1 == close(pipex->infile))
		(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
		(_error(ERR_DUP), free_array(pipex->paths), exit(1));
	if (-1 == dup2(fd[pipex->cmd_num - 2][READ_END], STDIN_FILENO))
		(_error(ERR_DUP), free_array(pipex->paths), exit(1));
	return (0);
}

int	middle_children(int i, t_pipex *pipex, int fd[pipex->cmd_num - 1][2])
{
	int	j;

	j = -1;
	while (++j < pipex->cmd_num - 1)
	{
		if (j != i)
			if (-1 == close(fd[j][READ_END]))
				(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
		if (j != i + 1)
			if (-1 == close(fd[j][WRITE_END]))
				(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	}
	if (-1 == close(pipex->infile))
		(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	if (-1 == close(pipex->outfile))
		(_error(ERR_CLOSE), free_array(pipex->paths), exit(1));
	if (-1 == dup2(fd[i][READ_END], STDIN_FILENO))
		(_error(ERR_DUP), free_array(pipex->paths), exit(1));
	if (-1 == dup2(fd[i + 1][WRITE_END], STDOUT_FILENO))
		(_error(ERR_DUP), free_array(pipex->paths), exit(1));
	return (0);
}

char	**cmd_find(char **cmd, char **path)
{
	char	*tmp;
	char	*temp;
	int		i;

	i = -1;
	tmp = ft_strjoin("/", cmd[0]);
	if (!tmp)
		return (free_array(cmd), print_error(ERR_MAL), NULL);
	while (*(path + ++i))
	{
		temp = ft_strjoin(*(path + i), tmp);
		if (!temp)
			return (free_array(cmd), free(tmp), print_error(ERR_MAL), NULL);
		if (!access(temp, F_OK | X_OK))
		{
			free(cmd[0]);
			cmd[0] = temp;
			return (free(tmp), cmd);
		}
		free(temp);
	}
	return (free_array(cmd), free(tmp), print_error(CMD_NOT_FOUND), NULL);
}

char	**cmd_check(char *cmd_string, t_pipex *pipex)
{
	char	**cmd;

	cmd = ft_split(cmd_string, ' ');
	if (!cmd)
		return (_error(ERR_MAL), NULL);
	if (!access(cmd[0], F_OK | X_OK))
		return (cmd);
	cmd = cmd_find(cmd, pipex->paths);
	if (!cmd)
		return (NULL);
	return (cmd);
}
