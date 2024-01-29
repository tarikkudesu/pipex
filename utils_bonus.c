/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:57 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/29 13:18:45 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	first_child(t_pipex *pipex, int fd[pipex->cmd_num - 1][2])
{
	int	j;

	j = 0;
	while (++j < pipex->cmd_num - 1)
	{
		if (-1 == close(fd[j][0]))
			return (_error(ERR_CLOSE));
		if (j != 0)
			if (-1 == close(fd[j][1]))
				return (_error(ERR_CLOSE));
	}
	if (-1 == close(pipex->outfile))
		return (_error(ERR_CLOSE));
	if (-1 == dup2(pipex->infile, 0))
		return (_error(ERR_DUP));
	if (-1 == dup2(fd[0][1], 1))
		return (_error(ERR_DUP));
	return (1);
}

int	last_child(t_pipex *pipex, int fd[pipex->cmd_num - 1][2])
{
	int	j;

	j = 0; 
	while (++j < pipex->cmd_num - 1)
	{
		if (-1 == close(fd[j][1]))
			return (_error(ERR_CLOSE));
		if (j != pipex->cmd_num - 2)
			if (-1 == close(fd[j][0]))
				return (_error(ERR_CLOSE));
	}
	if (-1 == close(pipex->infile))
		return (_error(ERR_CLOSE));
	if (-1 == dup2(pipex->outfile, 1))
		return (_error(ERR_DUP));
	if (-1 == dup2(fd[pipex->cmd_num - 2][0], 0))
		return (_error(ERR_DUP));
	return (1);
}

int	middle_children(int i, t_pipex *pipex, int fd[pipex->cmd_num - 1][2])
{
	int	j;

	j = 0;
	while (++j < pipex->cmd_num - 1)
	{
		if (j != i)
			if (-1 == close(fd[j][0]))
				return (_error(ERR_CLOSE));
		if (j != i + 1)
			if (-1 == close(fd[j][1]))
				return (_error(ERR_CLOSE));
	}
	if (-1 == close(pipex->infile))
		return (_error(ERR_CLOSE));
	if (-1 == close(pipex->outfile))
		return (_error(ERR_CLOSE));
	if (-1 == dup2(fd[i][0], 0))
		return (_error(ERR_DUP));
	if (-1 == dup2(fd[i + 1][1], 1))
		return (_error(ERR_DUP));
	return (1);
}

char	**cmd_find(char **cmd, char **path)
{
	char	*tmp;
	char	*temp;
	int		i;

	i = -1;
	tmp = ft_strjoin("/", cmd[0]);
	if (!tmp)
		return (free_array(cmd), _error_(ERR_MAL));
	while (*(path + ++i))
	{
		temp = ft_strjoin(*(path + i), tmp);
		if (!temp)
			return (free_array(cmd), free(tmp), _error_(ERR_MAL));
		if (!access(temp, F_OK | X_OK))
		{
			free(cmd[0]);
			cmd[0] = temp;
			return (free(tmp), cmd);
		}
		free(temp);
	}
	return (free_array(cmd), free(tmp), _error_(CMD_NOT_FOUND));
}

char	**cmd_check(char *cmd_string, t_pipex *pipex)
{
	char	**cmd;
	int		i;

	i = -1;
	cmd = ft_split(cmd_string, ' ');
	if (!cmd)
		return (_error_(ERR_MAL));
	if (!access(cmd[0], F_OK | X_OK))
		return (cmd);
	cmd = cmd_find(cmd, pipex->paths);
	if (!cmd)
		return (cmd = NULL, NULL);
	return (cmd);
}
