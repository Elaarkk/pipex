/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:17:39 by acolonne          #+#    #+#             */
/*   Updated: 2025/02/17 16:29:52 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	pid_t	child;
	int		status_code;
}				t_cmd;

char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_strjoin(char *s1, char *s2);

char	**parse_path_dir(char *path);

char	**ft_split(char const *s, char c);

void	ft_free_split(char **split);

char	*check_cmd(char *cmd1, char **path);

char	*check_local(char *cmd1);

char	*skip_cmd(char *cmd);

void	free_cmd(t_cmd *cmd1, t_cmd *cmd2);

int		ft_strlen(char *s);

void	ft_exit(t_cmd *cmd1, t_cmd *cmd2);

char	**get_path(char **env);

void	parse_cmd(t_cmd *cmd1, t_cmd *cmd2, char **path, char **argv);

char	**free_split(char **split, int a);

void	ft_putstr_fd(char *s, int fd);

void	exit_msg(char *s);

int		close_two_fd(int fd1, int fd2);

int		command_one(int fd[2], int pipefd[2], t_cmd *cmd, char **env);

int		command_two(int fd[2], int pipefd[2], t_cmd *cmd, char **env);

int		first_child(int fd[2], t_cmd *cmd, char **env, int pipefd[2]);

int		second_child(int fd[2], t_cmd *cmd, char **env, int pipefd[2]);

#endif
