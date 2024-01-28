/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/26 19:00:44 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	print_array_of_strings(char **array)
{
	int	i;

	i = 0;
	while (*(array + i))
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	find_cmd1(t_pipex *pipex, char *cmd, char **path)
{
	char	*tmp;
	int		i;

	i = -1;
	while (*(path + ++i))
	{
		tmp = ft_strjoin(*(path + i), cmd);
		if (!tmp)
			return (_error(ERR_MAL));
		if (access(tmp, F_OK) && access(tmp, X_OK))
		{
			tmp = ft_strjoin(*(path + i), cmd);
			free(pipex->cmd1[0]);
			pipex->cmd1[0] = tmp;
			return (0);
		}
		free(tmp);
	}
	return (_error(CMD_NOT_FOUND));
}

int	check_cmd1(t_pipex *pipex)
{
	char	*tmp;

	tmp = ft_strjoin("/", pipex->cmd1[0]);
	if (!tmp)
		return (_error(ERR_MAL));
	if (find_cmd1(pipex, tmp, pipex->paths))
		return (1);
	free(tmp);
	return (0);
}

int	find_cmd2(t_pipex *pipex, char *cmd, char **path)
{
	char	*tmp;
	int		i;

	i = -1;
	while (*(path + ++i))
	{
		tmp = ft_strjoin(*(path + i), cmd);
		if (!tmp)
			return (_error(ERR_MAL));
		if (access(tmp, F_OK) && access(tmp, X_OK))
		{
			tmp = ft_strjoin(*(path + i), cmd);
			free(pipex->cmd2[0]);
			pipex->cmd2[0] = tmp;
			break ;
		}
		free(tmp);
	}
	return (_error(CMD_NOT_FOUND));
}

int	check_cmd2(t_pipex *pipex)
{
	char	*tmp;

	tmp = ft_strjoin("/", pipex->cmd2[0]);
	if (!tmp)
		return (_error(ERR_MAL));
	if (find_cmd2(pipex, tmp, pipex->paths))
		return (1);
	free(tmp);
	return (0);
}

void	*child1_process(t_pipex *pipex)
{
	if (check_cmd1(pipex))
		return (NULL);
	print_array_of_strings(pipex->cmd1);
	close(pipex->outfile);
	close(pipex->pipe_fd[READ_END]);
	if (-1 == dup2(pipex->infile, STDIN_FILENO))
		return (_error_(ERR_DUP));
	if (-1 == dup2(pipex->pipe_fd[WRITE_END], STDOUT_FILENO))
		return (_error_(ERR_DUP));
	close(pipex->infile);
	close(pipex->pipe_fd[WRITE_END]);
	execve(pipex->cmd1[0], pipex->cmd1, pipex->env);
	return (_error_(ERR_EXECVE));
}

void	*child2_process(t_pipex *pipex)
{
	close(pipex->pipe_fd[WRITE_END]);
	close(pipex->infile);
	if (-1 == dup2(pipex->outfile, STDOUT_FILENO))
		return (_error_(ERR_DUP));
	if (-1 == dup2(pipex->pipe_fd[READ_END], STDIN_FILENO))
		return (_error_(ERR_DUP));
	close(pipex->outfile);
	close(pipex->pipe_fd[READ_END]);
	if (check_cmd2(pipex))
		return (NULL);
	printf("--- %s\n", pipex->cmd2[0]);
	execve(pipex->cmd2[0], pipex->cmd2, pipex->env);
	return (_error_(ERR_EXECVE));
}

int	close_fds(t_pipex pipex)
{
	if (close(pipex.infile) == -1)
		perror(ERR_CLOSE);
	if (close(pipex.outfile) == -1)
		perror(ERR_CLOSE);
	if (close(pipex.pipe_fd[READ_END]) == -1)
		perror(ERR_CLOSE);
	if (close(pipex.pipe_fd[WRITE_END]) == -1)
		perror(ERR_CLOSE);
	return (1);
}

int	pipe_it(t_pipex *pipex)
{
	pid_t	child1;
	// pid_t	child2;

	if (pipe(pipex->pipe_fd) == -1)
		return (_error(ERR_PIPE));
	child1 = fork();
	if (-1 == child1)
		return (_error(ERR_FORK));
	if (0 == child1)
		if (!child1_process(pipex))
			return (1);
	// child2 = fork();
	// if (-1 == child2)
	// 	return (_error(ERR_FORK));
	// if (0 == child2)
	// 	if (!child2_process(pipex))
	// 		return (1);
	if (!close_fds(*pipex))
		return (1);
	waitpid(child1, NULL, 0);
	// waitpid(child2, NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		_error(ERR_ARG);
		exit(1);
	}
	pipex.av = av;
	pipex.env = env;
	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
	pipex.paths = NULL;
	if (parcing(&pipex))
		_exit_pipex(pipex, 2);
	if (pipe_it(&pipex))
		_exit_pipex(pipex, 2);
	// done();
}
