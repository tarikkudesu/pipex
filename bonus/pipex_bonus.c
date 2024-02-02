/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 17:34:03 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_pip *pipex)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (-1 == fd)
		(free_struct_bonus(pipex), perror(ERR_OPEN), exit(EXIT_FAILURE));
	line = NULL;
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			(free_struct_bonus(pipex), perror(ERR_GNL), exit(EXIT_FAILURE));
		if (!ft_strncmp(line, pipex->delimiter, ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		(ft_putstr_fd(line, fd), free(line));
	}
	if (-1 == close(fd))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
}

int	main(int ac, char **av, char **environ)
{
	t_pip	pipex;

	if (ac < 5)
		(ft_putstr_fd(ERR_ARG, 2), exit(EXIT_FAILURE));
	if (0 == ft_strncmp(av[1], "here_doc", 8))
	{
		parsing_here_doc(&pipex, ac, av, environ);
		here_doc(&pipex);
	}
	else
		parsing(&pipex, ac, av, environ);
	pipex_mult_cmd(&pipex);
	(free_struct_bonus(&pipex), exit(EXIT_FAILURE));
}
