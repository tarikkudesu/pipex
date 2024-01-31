/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:57 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/31 12:07:37 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_process(t_pip *pipex, int fd[2])
{
	pipex->outfile = open(pipex->argv[pipex->argc - 1], \
	O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfile == -1)
		(p_error(ERR_OPEN), exit(1));
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
	if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
		(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
	// dprintf(1, "shiiiiiiiiiiit\n");
	// if (-1 == close(fd[WRITE_END]))
	// 	(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
	// if (-1 == close(fd[READ_END]))
	// 	(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
}

void	processes(t_pip *pipex, int fd[2])
{
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
	if (-1 == dup2(fd[WRITE_END], STDOUT_FILENO))
		(p_error(ERR_DUP), free_struct_bonus(pipex), exit(1));
	// if (-1 == close(fd[WRITE_END]))
	// 	(p_error(ERR_CLOSE), free_struct_bonus(pipex), exit(1));
}

int	cmd_find(char *cmd, char **path)
{
	char	*temp;
	int		i;

	i = -1;
	while (*(path + ++i))
	{
		temp = ft_strjoin(*(path + i), cmd);
		if (!temp)
			return (free(cmd), print_error(ERR_MAL), 1);
		if (!access(temp, F_OK | X_OK))
			return (free(temp), free(cmd), 0);
		free(temp);
	}
	return (free(cmd), 1);
}

char	**cmd_check(char *cmd_string, t_pip *pipex)
{
	char	**cmd;
	char	*tmp;

	cmd = ft_split(cmd_string, ' ');
	if (!cmd)
		return (p_error(ERR_MAL), NULL);
	if (!access(cmd[0], F_OK | X_OK))
		return (cmd);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		if (!access(cmd[0], F_OK | X_OK))
			return (cmd);
	tmp = ft_strjoin("/", cmd[0]);
	if (!tmp)
		return (free_array(cmd), print_error(ERR_MAL), NULL);
	if (cmd_find(tmp, pipex->paths))
		return (free_array(cmd), p_error(CMD_NOT_FOUND), NULL);
	return (cmd);
}
