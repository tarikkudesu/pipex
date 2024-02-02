/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 14:58:31 by tamehri          ###   ########.fr       */
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
		line = get_next_line(0);
		if (!line)
			(free_struct_bonus(pipex), perror(ERR_GNL), exit(EXIT_FAILURE));
		if (!ft_strncmp(line, pipex->argv[2], ft_strlen(pipex->argv[2])))
		{
			free(line);
			break ;
		}
		(ft_putstr_fd(line, fd), free(line));
	}
	if (-1 == close(fd))
		(free_struct_bonus(pipex), perror(ERR_CLOSE), exit(EXIT_FAILURE));
}

void	pipex_here_doc(t_pip *pipex)
{
	int	infile;

	here_doc(pipex);
	infile = open(".tmp", O_RDONLY);
	if (-1 == infile)
		(free_struct_bonus(pipex), perror(ERR_OPEN), exit(EXIT_FAILURE));
	pipex->infile = infile;
	pipe_it(pipex);
}

int	main(int ac, char **av, char **environ)
{
	t_pip	pipex;

	if (ac < 5)
		(ft_putstr_fd(ERR_ARG, 2), exit(EXIT_FAILURE));
	pipex.argc = ac;
	pipex.argv = av;
	pipex.pids = NULL;
	pipex.cmd_num = ac - 3;
	pipex.environ = environ;
	if (0 == ft_strncmp(av[1], "here_doc", 8))
	{
		if (ac != 6)
			(ft_putstr_fd(ERR_ARG, 2), exit(EXIT_FAILURE));
		pipex.cmd_num = 2;
		parsing(&pipex);
		pipex_here_doc(&pipex);
	}
	else
	{
		parsing(&pipex);
		pipex_mult_cmd(&pipex);
	}
	(free_struct_bonus(&pipex), exit(EXIT_FAILURE));
}
