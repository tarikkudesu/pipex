/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:28:28 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 14:58:13 by tamehri          ###   ########.fr       */
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

void	parsing(t_pip *pipex)
{
	pipex->paths = find_path(pipex->environ);
	if (!pipex->paths)
		(perror(ERR_MAL), exit(EXIT_FAILURE));
	pipex->pids = malloc(sizeof(int) * pipex->cmd_num);
	if (!pipex->pids)
		(perror(ERR_MAL), exit(EXIT_FAILURE));
}
