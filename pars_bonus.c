/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:28:28 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/28 18:30:43 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**find_path(char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	if (!env || !*env)
		return (NULL);
	while (*(env + ++i))
	{
		if (!ft_strncmp(*(env + i), "PATH=", 5))
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (NULL);
			break ;
		}
	}
	return (path);
}

int	parsing(t_pipex *pipex)
{
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
		return (_error(ERR_OPEN));
	pipex->outfile = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfile == -1)
		return (_error(ERR_OPEN));
	pipex->paths = find_path(pipex->environ);
	if (!pipex->paths)
		return (_error(ERR_PATH));
	return (0);
}