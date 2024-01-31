/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:03:18 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/29 13:11:18 by tamehri          ###   ########.fr       */
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
			return (p_error(ERR_MAL));
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
		{
			free(pipex->cmd1[0]);
			pipex->cmd1[0] = tmp;
			return (0);
		}
		free(tmp);
	}
	return (p_error(CMD_NOT_FOUND));
}

int	check_cmd1(t_pipex *pipex)
{
	char	*tmp;

	if (pipex->cmd1[0][0] == '/' || pipex->cmd2[0][0] == '.')
		if (!access(pipex->cmd1[0], F_OK | X_OK))
			return (0);
	tmp = ft_strjoin("/", pipex->cmd1[0]);
	if (!tmp)
		return (p_error(ERR_MAL));
	if (find_cmd1(pipex, tmp, pipex->paths))
		(free(tmp), free_struct(pipex), exit(127));
	return (free(tmp), 0);
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
			return (p_error(ERR_MAL));
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
		{
			free(pipex->cmd2[0]);
			pipex->cmd2[0] = tmp;
			return (0);
		}
		free(tmp);
	}
	return (p_error(CMD_NOT_FOUND));
}

int	check_cmd2(t_pipex *pipex)
{
	char	*tmp;

	if (!access(pipex->cmd2[0], F_OK | X_OK))
		return (0);
	if (pipex->cmd2[0][0] == '/' || pipex->cmd2[0][0] == '.')
		if (!access(pipex->cmd2[0], F_OK | X_OK))
			return (0);
	tmp = ft_strjoin("/", pipex->cmd2[0]);
	if (!tmp)
		return (p_error(ERR_MAL));
	if (find_cmd2(pipex, tmp, pipex->paths))
		(free(tmp), free_struct(pipex), exit(127));
	return (free(tmp), 0);
}
