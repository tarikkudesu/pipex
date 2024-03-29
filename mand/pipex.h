/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:26:39 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/13 09:41:36 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define READ_END		0
# define WRITE_END		1
# define ERR_ARG		"Wrong number of arguments\n"
# define ERR_MAL		"MALLOC ERROR"
# define ERR_FORK		"FORK ERROR"
# define ERR_PIPE		"PIPE ERROR"
# define ERR_DUP		"DUP2 ERROR"
# define ERR_OPEN		"OPEN ERROR"
# define ERR_EXECVE		"EXECVE ERROR"
# define CMD_NOT_FOUND	"COMMAND NOT FOUND"

typedef struct s_pip	t_pip;
typedef struct s_cmd	t_cmd;

struct	s_pip
{
	int		argc;
	int		fd[2];
	int		infile;
	int		outfile;
	int		*pids;
	char	**argv;
	char	**paths;
	char	**environ;
};

/* HELP FUNCTIONS */
size_t		ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/* FUNCTIONS */
int			cmd_find(char *cmd, char **path);
char		*get_path(char *cmd, char **path);
char		**cmd_check(char *cmd_string, t_pip *pipex);
void		execute_cmd(char *cmd_string, t_pip *pipex);
void		exit_status(int exit_code, int *i);
void		free_struct(t_pip *pipex);
void		free_array(char **array);
char		**find_path(char **env);
void		parsing(t_pip *pipex);
void		second_child(t_pip *pipex);
void		first_child(t_pip *pipex);
void		execute(t_pip *pipex);
void		pipe_it(t_pip *pipex);

#endif