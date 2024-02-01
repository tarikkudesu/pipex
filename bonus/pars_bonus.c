/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:28:28 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/01 13:55:09 by tamehri          ###   ########.fr       */
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

void	parsing(t_pip *pipex, int bool)
{
	if (bool)
	{
		pipex->infile = open(pipex->argv[1], O_RDONLY);
		if (pipex->infile == -1)
			(p_error(ERR_OPEN), free_struct_bonus(pipex), exit(1));
		pipex->outfile = open(pipex->argv[pipex->argc - 1], \
		O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (pipex->outfile == -1)
			(p_error(ERR_OPEN), exit(1));
	}
	else
	{
		pipex->outfile = open(pipex->argv[pipex->argc - 1], \
		O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (pipex->outfile == -1)
			(p_error(ERR_OPEN), exit(1));
	}
	pipex->paths = find_path(pipex->environ);
	if (!pipex->paths)
		(p_error(ERR_MAL), exit(1));
}
