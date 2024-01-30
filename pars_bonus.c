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
			return(free(pipes), p_error(ERR_MAL), NULL);
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
		return (p_error(ERR_MAL), NULL);
	return (pid);
}

void	parsing(t_pip *pipex)
{
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
		(p_error(ERR_OPEN), exit(1));
	pipex->outfile = open(pipex->argv[pipex->argc - 1], \
	O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfile == -1)
		(p_error(ERR_OPEN), exit(1));
	pipex->paths = find_path(pipex->environ);
	if (!pipex->paths)
		(p_error(ERR_MAL), exit(1));
	pipex->pipes = init_pipes(pipex->cmd_num - 1);
	if (!pipex->pipes)
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	pipex->pid = init_pid(pipex->cmd_num);
	if (!pipex->pid)
		(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
}
