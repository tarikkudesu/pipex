/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:57:13 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/26 20:24:53 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char	**check_cmd(char **cmd, char **path)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*tmp_cmd;

// 	i = -1;
// 	while (*(path + ++i))
// 	{
// 		tmp_cmd = ft_strjoin(*(path + i), *cmd);
// 		if (!tmp_cmd)
// 			return (_error_(ERR_MAL));
// 		if (access(tmp_cmd, F_OK) == 0 || access(tmp_cmd, X_OK) == 0)
// 		{
// 			tmp = *cmd;
// 			*cmd = tmp_cmd;
// 			return (free(tmp), cmd);
// 		}
// 		free(tmp_cmd);
// 	}
// 	return (_error_(CMD_NOT_FOUND));
// }

// char	**find_cmd(char *cmd_string, t_pipex *pipex)
// {
// 	char	**cmd;
// 	char	**path;
// 	char	*tmp;

// 	path = find_path(pipex->env);
// 	if (!path)
// 		return (NULL);
// 	cmd = ft_split(cmd_string, ' ');
// 	if (!cmd)
// 	{
// 		ft_error(path);
// 		return (_error_(ERR_MAL));
// 	}
// 	tmp = *cmd;
// 	*cmd = ft_strjoin("/", *cmd);
// 	free(tmp);
// 	if (!*cmd)
// 	{
// 		ft_error(path);
// 		return (_error_(ERR_MAL));
// 	}
// 	cmd = check_cmd(cmd, path);
// 	if (!cmd)
// 	{
// 		ft_error(path);
// 		return (NULL);
// 	}
// 	ft_error(path);
// 	return (cmd);
// }

char	**find_path(char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	if (!env || !*env)
		return (_error_(ERR_PATH));
	while (*(env + ++i))
	{
		if (!ft_strncmp(*(env + i), "PATH=", 5))
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (_error_(ERR_MAL));
			break ;
		}
	}
	return (path);
}

int	parcing(t_pipex **pipex)
{
	(*pipex)->infile = open((*pipex)->av[1], O_RDONLY);
	if ((*pipex)->infile == -1)
		return (_error(ERR_OPEN));
	(*pipex)->outfile = open((*pipex)->av[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if ((*pipex)->outfile == -1)
		return (_error(ERR_OPEN));
	(*pipex)->paths = find_path((*pipex)->env);
	if (!(*pipex)->paths)
		return (1);
	(*pipex)->cmd1 = ft_split((*pipex)->av[2], ' ');
	(*pipex)->cmd2 = ft_split((*pipex)->av[3], ' ');
	return (0);
}
