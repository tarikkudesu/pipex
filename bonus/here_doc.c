/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:46 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/01 15:38:40 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


void	here_doc(t_pip *pipex)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if ( -1 == fd)
		(free_struct_bonus(pipex), p_error(ERR_OPEN), exit(1));
	line = NULL;
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			(free_struct_bonus(pipex), p_error(ERR_GNL), exit(1));
		if (!ft_strncmp(line, pipex->argv[2], ft_strlen(pipex->argv[2])))
		{
			free(line);
			break ;
		}
		(ft_putstr_fd(line, fd), free(line));
	}
	if (-1 == close(fd))
		(free_struct_bonus(pipex), p_error(ERR_CLOSE), exit(1));
}

void	pipex_here_doc(t_pip *pipex)
{
	int	infile;

	here_doc(pipex);
	infile = open(".tmp", O_RDONLY);
	if (-1 == infile)
		(free_struct_bonus(pipex), p_error(ERR_OPEN), exit(1));
	pipex->infile = infile;
}
