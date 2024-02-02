/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:15:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 09:49:03 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_struct_bonus(t_pip *pipex)
{
	if (pipex->paths)
		free_array(pipex->paths);
	if (pipex->cmd2)
		free_array(pipex->cmd2);
	if (pipex->cmd1)
		free_array(pipex->cmd1);
	if (pipex->pid)
		free(pipex->pid);
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

int	p_error(char *s)
{
	perror(s);
	return (1);
}

void	print_error(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
}
