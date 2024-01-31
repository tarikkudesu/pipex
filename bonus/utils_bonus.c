/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:57 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/31 16:02:19 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	cmd_find(char *cmd, char **path)
{
	char	*temp;
	int		i;

	i = -1;
	while (*(path + ++i))
	{
		temp = ft_strjoin(*(path + i), cmd);
		if (!temp)
			return (free(cmd), print_error(ERR_MAL), 1);
		if (!access(temp, F_OK | X_OK))
			return (free(temp), free(cmd), 0);
		free(temp);
	}
	return (free(cmd), 1);
}

char	**cmd_check(char *cmd_string, t_pip *pipex)
{
	char	**cmd;
	char	*tmp;

	cmd = ft_split(cmd_string, ' ');
	if (!cmd)
		return (p_error(ERR_MAL), NULL);
	if (!access(cmd[0], F_OK | X_OK))
		return (cmd);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		if (!access(cmd[0], F_OK | X_OK))
			return (cmd);
	tmp = ft_strjoin("/", cmd[0]);
	if (!tmp)
		return (free_array(cmd), print_error(ERR_MAL), NULL);
	if (cmd_find(tmp, pipex->paths))
		return (free_array(cmd), p_error(CMD_NOT_FOUND), NULL);
	return (cmd);
}
