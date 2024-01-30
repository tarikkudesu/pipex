/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:01:24 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/28 19:40:44 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define BLUE	"\033[1;34m"
# define RESET	"\033[0m"
# define READ_END		0
# define WRITE_END		1
# define LINE_			"---------------------------------------------------\n"
# define ERR_ARG		"WRONG ARGUMENTS\n"
# define ERR_MAL		"MALLOC ERROR"
# define ERR_PATH		"PATH ERROR"
# define ERR_FORK		"FORK ERROR"
# define ERR_PIPE		"PIPE ERROR"
# define ERR_DUP		"DUP2 ERROR"
# define ERR_WAIT		"WAIT ERROR"
# define ERR_OPEN		"OPEN ERROR"
# define ERR_CLOSE		"CLOSE ERROR"
# define ERR_WRITE		"WRITE ERROR"
# define ERR_EXECVE		"EXECVE ERROR"
# define ERR_PERM		"PERMISSION ERROR"
# define CMD_NOT_FOUND	"COMMAND NOT FOUND"
# define COMPILED		"-----------\tCOMPILED_SUCCESSFULLY\t-----------\n"

typedef struct s_pipex	t_pipex;

struct	s_pipex
{
	int		pipe_fd[2];
	int		outfile;
	int		infile;
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	char	**env;
	char	**av;
};

size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);

void		free_struct(t_pipex *pipex);
void		print_error(char *s);
int			_error(char *s);
int			find_cmd1(t_pipex *pipex, char *cmd, char **path);
int			check_cmd1(t_pipex *pipex);
int			find_cmd2(t_pipex *pipex, char *cmd, char **path);
int			check_cmd2(t_pipex *pipex);
int			child1_process(t_pipex *pipex);
int			child2_process(t_pipex *pipex);
int			pipe_it(t_pipex *pipex);
char		**find_path(char **env);
int			parsing(t_pipex *pipex);

#endif
