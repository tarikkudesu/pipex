/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:57 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 15:03:25 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	cmd_find(char *cmd, char **path)
{
	char	*temp;
	int		i;

	i = -1;
	while (*(path + ++i))
	{
		temp = ft_strjoin(*(path + i), cmd);
		if (!temp)
			return (free(cmd), 1);
		if (!access(temp, F_OK | X_OK))
			return (free(temp), free(cmd), 0);
		free(temp);
	}
	return (free(cmd), 1);
}

char	*get_path(char *cmd, char **path)
{
	char	*temp;
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (ft_putstr_fd(ERR_MAL, 2), NULL);
	while (*(path + ++i))
	{
		temp = ft_strjoin(*(path + i), tmp);
		if (!temp)
			return (free(tmp), ft_putstr_fd(ERR_MAL, 2), NULL);
		if (!access(temp, F_OK | X_OK))
			return (free(tmp), temp);
		free(temp);
	}
	free(tmp);
	return (NULL);
}

char	**cmd_check(char *cmd_string, t_pip *pipex)
{
	char	**cmd;
	char	*tmp;

	cmd = ft_split(cmd_string, ' ');
	if (!cmd)
		return (NULL);
	if (!access(cmd[0], F_OK | X_OK))
		return (cmd);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		if (!access(cmd[0], F_OK | X_OK))
			return (cmd);
	tmp = ft_strjoin("/", cmd[0]);
	if (!tmp)
		return (free_array(cmd), NULL);
	if (cmd_find(tmp, pipex->paths))
		return (free_array(cmd), NULL);
	return (cmd);
}

void	execute_cmd(char *cmd_string, t_pip *pipex)
{
	char	**cmd;
	char	*path;

	cmd = cmd_check(cmd_string, pipex);
	if (!cmd)
		(free_struct_bonus(pipex), perror(CMD_NOT_FOUND), exit(EXIT_FAILURE));
	path = get_path(cmd[0], pipex->paths);
	if (!path)
		(free_array(cmd), free_struct_bonus(pipex), \
		perror(CMD_NOT_FOUND), exit(EXIT_FAILURE));
	execve(path, cmd, pipex->environ);
	(free(path), free_array(cmd), \
	free_struct_bonus(pipex), perror(ERR_EXECVE), exit(EXIT_FAILURE));
}
