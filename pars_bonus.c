/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:28:28 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/30 15:10:16 by tamehri          ###   ########.fr       */
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

int	**init_pipes(int size)
{
	int	i;
	int	**pipes;

	pipes = malloc((size + 1) * sizeof(int));
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		*(pipes + i) = malloc(2 * sizeof(int));
		if (!*(pipes + i))
		{
			while (i-- >= 0)
				free(*(pipes + i));
			return(free(pipes), _error(ERR_MAL), NULL);
		}
	}
	*(pipes + i) = NULL;
	return (pipes);
}

int	*init_pid(int size)
{
	int	*pid;

	pid = malloc(sizeof(int) * size);
	if (!pid)
		return (_error(ERR_MAL), NULL);
	return (pid);
}

int	parsing(t_pipex *pipex)
{
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
		return (_error(ERR_OPEN));
	pipex->outfile = open(pipex->argv[pipex->argc - 1], \
	O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfile == -1)
		return (_error(ERR_OPEN));
	pipex->paths = find_path(pipex->environ);
	if (!pipex->paths)
		return (_error(ERR_PATH));
	pipex->pipes = init_pipes(pipex->cmd_num - 1);
	if (!pipex->pipes)
		return (free_array (pipex->paths), _error(ERR_MAL));
	pipex->pid = init_pid(pipex->cmd_num);
	if (!pipex->pid)
		(free_int_array(pipex->pipes), free_array (pipex->paths), return (_error(ERR_MAL)));
	return (0);
}
