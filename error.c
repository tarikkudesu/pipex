/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:15:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/29 10:38:16 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int i;

	i = -1;
	while (*(array + ++i))
		free(*(array + i));
	free(array);
}

void	free_struct_bonus(t_pipex *pipex)
{
	if (pipex->paths)
		free_array(pipex->paths);
}

void	free_struct(t_pipex *pipex)
{
	if (pipex->paths)
		free_array(pipex->paths);
	if (pipex->cmd1)
		free_array(pipex->cmd1);
	if (pipex->cmd2)
		free_array(pipex->cmd2);
}

int	_error(char *s)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	perror(s);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	return (1);
}
