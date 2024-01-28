/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/28 18:52:16 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


void	pipex_mult_cmd(t_pipex *pipex)
{
	int		i;
	int		pid;

	i = -1;
	while (++i < pipex->cmd_num)
		execute_cmd(pipex->argv[i + 2], pipex);
	
}

int main(int ac, char **av, char **environ)
{
	t_pipex	pipex;
	
	if (ac < 5)
	{
		_error(ERR_ARG);
		exit(1);
	}
	pipex.argv = av;
	pipex.argv = ac;
	pipex.environ = environ;
	pipex.cmd_num = ac - 3;
	if (0 == ft_strncmp(av[1], "here_doc", 8))
		pipex_here_doc(&pipex);
	else
		pipex_mult_cmd(&pipex);
	free_struct(&pipex);
	exit(EXIT_SUCCESS);
}