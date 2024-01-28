/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:03:18 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/28 11:24:48 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_cmd1(t_pipex *pipex, char *cmd, char **path)
{
	char	*tmp;
	int		i;

	i = -1;
	while (*(path + ++i))
	{
		tmp = ft_strjoin(*(path + i), cmd);
		if (!tmp)
			return (_error(ERR_MAL));
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
		{
			tmp = ft_strjoin(*(path + i), cmd);
			free(pipex->cmd1[0]);
			pipex->cmd1[0] = tmp;
			return (0);
		}
		free(tmp);
	}
	return (_error(CMD_NOT_FOUND));
}

int	check_cmd1(t_pipex *pipex)
{
	char	*tmp;
	int		i;

	if (pipex->cmd1[0][0] == '/')
	{
		i = -1;
		while (pipex->paths[++i])
			if (access(pipex->cmd1[0], F_OK) == 0 \
			&& access(pipex->cmd1[0], X_OK) == 0)
				return (0);
	}
	tmp = ft_strjoin("/", pipex->cmd1[0]);
	if (!tmp)
		return (_error(ERR_MAL));
	if (find_cmd1(pipex, tmp, pipex->paths))
		return (1);
	free(tmp);
	return (0);
}

int	find_cmd2(t_pipex *pipex, char *cmd, char **path)
{
	char	*tmp;
	int		i;

	i = -1;
	while (*(path + ++i))
	{
		tmp = ft_strjoin(*(path + i), cmd);
		if (!tmp)
			return (_error(ERR_MAL));
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
		{
			tmp = ft_strjoin(*(path + i), cmd);
			free(pipex->cmd2[0]);
			pipex->cmd2[0] = tmp;
			break ;
		}
		free(tmp);
	}
	return (_error(CMD_NOT_FOUND));
}

int	check_cmd2(t_pipex *pipex)
{
	char	*tmp;

	tmp = ft_strjoin("/", pipex->cmd2[0]);
	if (!tmp)
		return (_error(ERR_MAL));
	if (find_cmd2(pipex, tmp, pipex->paths))
		return (1);
	free(tmp);
	return (0);
}
