/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:15:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/12 18:08:08 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_status(int exit_code, int *j)
{
	if (0 == exit_code)
		(*j)++;
}

void	free_struct_bonus(t_pip *pipex)
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
