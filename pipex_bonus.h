/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:26:39 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/29 12:13:13 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
# define ERR_ARG		"WRONG ARGUMENTS"
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
typedef struct s_cmd	t_cmd;

struct	s_pipex
{
	int		argc;
	int		infile;
	int		outfile;
	int		cmd_num;
	char	**argv;
	char	**paths;
	char	**environ;
};

struct t_cmd
{
	int	*fd[2];
};

size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		free_array(char **array);
void		free_struct(t_pipex *pipex);
void		_exit_pipex(t_pipex *pipex, int err);
void		*_error_(char *s);
int			_error(char *s);


int			parsing(t_pipex *pipex);


/* FUNCTIONS */
int	first_child(t_pipex *pipex, int fd[pipex->cmd_num - 1][2]);
int	last_child(t_pipex *pipex, int fd[pipex->cmd_num - 1][2]);
void	middle_children(int i, t_pipex *pipex, int fd[pipex->cmd_num - 1][2]);
char	*cmd_find(t_pipex *pipex, char **cmd, char **path);
char	**cmd_check(char *cmd_string, t_pipex *pipex);
static int	close_fds(t_pipex *pipex, int fd[pipex->cmd_num][2]);
void	execute(t_pipex *pipex, char *cmd_string, int i, int fd[pipex->cmd_num - 1]);
int	pipex_mult_cmd(t_pipex *pipex);
char	**find_path(char **env);

#endif