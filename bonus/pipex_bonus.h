/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:26:39 by tamehri           #+#    #+#             */
/*   Updated: 2024/01/31 16:05:23 by tamehri          ###   ########.fr       */
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
# define ERR_ARG		"WRONG NUMBER OF ARGUMENTS\n"
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

typedef struct s_pip	t_pip;
typedef struct s_cmd	t_cmd;

struct	s_pip
{
	int		argc;
	int		infile;
	int		outfile;
	int		cmd_num;
	int		fd[2];
	char	**argv;
	char	**paths;
	char	**environ;
};

size_t		ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void	free_struct_bonus(t_pip *pipex);
void	free_array(char **array);
int		p_error(char *s);
void	print_error(char *s);
char	*get_path(char *cmd, char **path);
int		cmd_find(char *cmd, char **path);
char	**cmd_check(char *cmd_string, t_pip *pipex);
char	**find_path(char **env);
void	parsing(t_pip *pipex);
void	execute_cmd(char *cmd_string, t_pip *pipex);
void	last_child(t_pip *pipex);
void	execute(t_pip *pipex, int i);
void	pipex_mult_cmd(t_pip *pipex);
int		pipex_here_doc(t_pip *pipex);

#endif