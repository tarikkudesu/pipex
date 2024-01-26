/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:24 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/26 20:24:11 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define BLUE	"\033[1;34m"
# define RESET	"\033[0m"
# define LINE_			"---------------------------------------------------\n"
# define READ_END		0
# define WRITE_END		1
# define ERR_MAL		"MALLOC ERROR"
# define ERR_ARG		"WRONG ARGUMENTS"
# define ERR_PATH		"PATH ERROR"
# define ERR_FORK		"FORK ERROR"
# define ERR_PIPE		"PIPE ERROR"
# define ERR_DUP		"DUP2 ERROR"
# define ERR_WAIT		"WAIT ERROR"
# define ERR_OPEN		"OPEN ERROR"
# define ERR_PERM		"PERMISSION ERROR"
# define ERR_WRITE		"WRITE ERROR"
# define ERR_EXECVE		"EXECVE ERROR"
# define CMD_NOT_FOUND	"COMMAND NOT FOUND"
# define COMPILED		"-----------\tCOMPILED_SUCCESSFULLY\t-----------\n"

typedef struct s_pipex	t_pipex;

struct	s_pipex
{
	int		pipe_fd[2];
	int		outfile;
	int		infile;
	char	**cmd1;
	char	**cmd2;
	char	**env;
	char	**av;
};

char		**ft_error(char **tab);
void		done(void);
void		*_error_(char *s);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			parcing(t_pipex *pipex);
int			_error(char *s);
void		ft_putstr_fd(char *s, int fd);
void		*child1_process(t_pipex **pipex);
void		*child2_process(t_pipex **pipex);
int			pipe_it(t_pipex **pipex);


#endif