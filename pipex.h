/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:24 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/25 17:27:27 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

// remove this
# include <stdio.h>
void ft_print_strs(char **strs);

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

# define ERROR "\n----\tError\t-----\n\n"
# define ERR_ARG "\n-----\tWrong number of arguments\t-----\n\n"
# define ERR_PATH "\n----\tPath error\t-----\n\n"
# define ERR_MAL "\n-----\tMalloc error\t-----\n\n"
# define ERR_FORK "\n-----\tFork error\t-----\n\n"
# define ERR_PIPE "\n-----\tPipe error\t-----\n\n"
# define ERR_DUP "\n-----\tDup error\t-----\n\n"
# define ERR_OPEN "\n-----\tOpen error\t-----\n\n"
# define ERR_WRITE "\n-----\tWrite error\t-----\n\n"
# define ERR_EXECVE "\n-----\tExecve error\t-----\n\n"
# define ERR_WAIT "\n-----\tWait error\t-----\n\n"
# define CMD_NOT_FOUND "\n-----\tCommand not found\t-----\n\n"
# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2
# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex	t_pipex;

struct	s_pipex
{
	int		pipe_fd[2];
	int		outfile;
	int		infile;
	char	**cmd1;
	char	**cmd2;
	char 	**env;
	char	**av;
};

/* FUNCTIONS */
void	*_error_(char *s);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		parcing(t_pipex *pipex);
int 	_error(char *s);
void	ft_putstr_fd(char *s, int fd);

#endif