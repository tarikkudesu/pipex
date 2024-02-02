/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:26:39 by tamehri           #+#    #+#             */
/*   Updated: 2024/02/02 17:19:53 by tamehri          ###   ########.fr       */
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

# define READ_END		0
# define WRITE_END		1
# define ERR_ARG		"Wrong number of arguments\n"
# define ERR_GNL		"GET_NEXT_LINE\n"
# define ERR_MAL		"MALLOC ERROR"
# define ERR_FORK		"FORK ERROR"
# define ERR_PIPE		"PIPE ERROR"
# define ERR_DUP		"DUP2 ERROR"
# define ERR_WAIT		"WAIT ERROR"
# define ERR_OPEN		"OPEN ERROR"
# define ERR_CLOSE		"CLOSE ERROR"
# define ERR_WRITE		"WRITE ERROR"
# define ERR_UNLINK		"UNLINK ERROR"
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
	int		cmd_num;
	int		*pids;
	char	**argv;
	char	**paths;
	char	**environ;
	char	*delimiter;
	char	*infilename;
	char	*outfilename;
};

/* LIBFT */
size_t		ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/* GET_NEXT_LINE */
size_t		ft_strlen_g(const char *s);
char		*ft_strdup_g(const char *s1);
char		*ft_strchr_g(const char *s);
char		*ft_strjoin_g(char *s1, char *s2);
char		*get_next_line(int fd);
char		*read_to_nl(char *stat, int fd);
char		*ft_before_nl(char *stat);
char		*ft_after_nl(char *stat);

/* FUNCTIONS */
void		exit_status(int exit_code, int *j);
void		free_struct_bonus(t_pip *pipex);
void		free_array(char **array);
int			cmd_find(char *cmd, char **path);
char		*get_path(char *cmd, char **path);
char		**cmd_check(char *cmd_string, t_pip *pipex);
void		execute_cmd(char *cmd_string, t_pip *pipex);
void		last_process(t_pip *pipex);
void		first_process(t_pip *pipex);
void		execute(t_pip *pipex, int i);
void		pipex_mult_cmd(t_pip *pipex);
void		here_doc(t_pip *pipex);
char		**find_path(char **env);
void		parsing_here_doc(t_pip *pipex, int ac, char **av, char **environ);
void		parsing(t_pip *pipex, int ac, char **av, char **environ);

#endif
