/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:15:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 14:40:21 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_status(int exit_code, int *j)
{
	if (0 == exit_code)
		(*j)++;
}

void	free_struct(t_pip *pipex)
{
	if (pipex->paths)
		free_array(pipex->paths);
	if (pipex->pids)
		free(pipex->pids);
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (*(array + ++i))
			free(*(array + i));
		free(array);
		array = NULL;
	}
}
