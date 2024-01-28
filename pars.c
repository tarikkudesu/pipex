/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:57:13 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/28 12:29:54 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	parsing(t_pipex *pipex)
{
	pipex->infile = open(pipex->av[1], O_RDONLY);
	if (pipex->infile == -1)
		return (_error(ERR_OPEN));
	pipex->outfile = open(pipex->av[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (pipex->outfile == -1)
		return (_error(ERR_OPEN));
	pipex->paths = find_path(pipex->env);
	if (!pipex->paths)
		return (1);
	pipex->cmd1 = ft_split(pipex->av[2], ' ');
	pipex->cmd2 = ft_split(pipex->av[3], ' ');
	return (0);
}
