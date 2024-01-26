/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/26 09:42:17 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_print_strs(char **strs)
{
    while (*strs)
    {
        ft_putstr_fd(*strs, 1);
        write(1, "\n", 1);
        strs++;
    }
}

void	*child1_process(t_pipex **pipex)
{
	close((*pipex)->outfile);
	close((*pipex)->pipe_fd[READ_END]);
	if (-1 == dup2((*pipex)->infile, STD_IN))
		return (_error_(ERR_DUP));
	if (-1 == dup2((*pipex)->pipe_fd[WRITE_END], STD_OUT))
		return (_error_(ERR_DUP));
	close((*pipex)->infile);
	close((*pipex)->pipe_fd[WRITE_END]);
	execve((*pipex)->cmd1[0], (*pipex)->cmd1, (*pipex)->env);
	return (_error_(ERR_EXECVE));
}

void	*child2_process(t_pipex **pipex)
{
	close(((*pipex))->pipe_fd[WRITE_END]);
	close((*pipex)->infile);
	if (-1 == dup2((*pipex)->outfile, STD_OUT))
		return (_error_(ERR_DUP));
	if (-1 == dup2((*pipex)->pipe_fd[READ_END], STD_IN))
		return (_error_(ERR_DUP));
	close((*pipex)->outfile);
	close((*pipex)->pipe_fd[READ_END]);
	execve((*pipex)->cmd2[0], (*pipex)->cmd2, (*pipex)->env);
	return (_error_(ERR_EXECVE));
}

void	*pipe_it(t_pipex **pipex)
{
	pid_t	child1;
	pid_t	child2;
	
	if (pipe((*pipex)->pipe_fd) == -1)
		return (_error_(ERR_PIPE));
	// printf("%d\t%d\n", (*pipex)->pipe_fd[0], (*pipex)->pipe_fd[1]);
	child1 = fork();
	if (-1 == child1)
		return (_error_(ERR_FORK));
	if (0 == child1)
		if (!child1_process(pipex))
			return (NULL);
	child2 = fork();
	if (-1 == child2)
		return (_error_(ERR_FORK));
	if (0 == child2)
		if (!child2_process(pipex))
			return (NULL);
	close((*pipex)->infile);
	close((*pipex)->outfile);
	close((*pipex)->pipe_fd[READ_END]);
	close((*pipex)->pipe_fd[WRITE_END]);
	waitpid(child1, NULL, 0);
	// waitpid(child2, NULL, 0);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	(void)ac;
	(void)av;
	if (ac != 5)
		return (_error(ERR_ARG));
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (_error(ERR_MAL));
	pipex->av = av;
	pipex->env = env;
	if (parcing(pipex))
		return (2);
	pipe_it(&pipex);
}
