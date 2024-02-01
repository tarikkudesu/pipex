/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:15:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/01 15:47:10 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_struct_bonus(t_pip *pipex)
{
	int	i;

	i = -1;
	if (pipex->paths)
	{
		while (*(pipex->paths + ++i))
			free(*(pipex->paths + i));
		free(pipex->paths);
	}
	i = -1;
	if (pipex->cmd2)
	{
		while (*(pipex->cmd2 + ++i))
			free(*(pipex->cmd2 + i));
		free(pipex->cmd2);
	}
	i = -1;
	if (pipex->cmd1)
	{
		while (*(pipex->cmd1 + ++i))
			free(*(pipex->cmd1 + i));
		free(pipex->cmd1);
	}
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
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	perror(s);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	return (1);
}

void	print_error(char *s)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(LINE_, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}
