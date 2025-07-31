/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:14:02 by acolonne          #+#    #+#             */
/*   Updated: 2025/02/17 16:40:38 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	command_one(int fd[2], int pipefd[2], t_cmd *cmd, char **env)
{
	close_two_fd(pipefd[0], fd[1]);
	dup2(fd[0], 0);
	dup2(pipefd[1], 1);
	close_two_fd(fd[0], pipefd[1]);
	if (cmd[0].cmd && fd[0] > -1)
	{
		if (execve(cmd[0].cmd, cmd[0].arg, env) == -1)
		{
			perror("command error");
			ft_exit(&cmd[0], &cmd[1]);
		}
	}
	ft_exit(&cmd[0], &cmd[1]);
	return (1);
}

int	command_two(int fd[2], int pipefd[2], t_cmd *cmd, char **env)
{
	close_two_fd(pipefd[1], fd[0]);
	dup2(fd[1], 1);
	dup2(pipefd[0], 0);
	close_two_fd(fd[1], pipefd[0]);
	if (cmd[1].cmd && fd[1] > -1)
	{
		if (execve(cmd[1].cmd, cmd[1].arg, env) == -1)
		{
			perror("command error");
			ft_exit(&cmd[0], &cmd[1]);
		}
	}
	ft_exit(&cmd[0], &cmd[1]);
	return (1);
}

int	first_child(int fd[2], t_cmd *cmd, char **env, int pipefd[2])
{
	cmd[0].child = fork();
	if (cmd[0].child < 0)
	{
		close_two_fd(pipefd[0], pipefd[1]);
		return (-1);
	}
	else if (cmd[0].child == 0)
		command_one(fd, pipefd, cmd, env);
	return (0);
}

int	second_child(int fd[2], t_cmd *cmd, char **env, int pipefd[2])
{
	cmd[1].child = fork();
	if (cmd[1].child < 0)
	{
		close_two_fd(pipefd[0], pipefd[1]);
		return (-1);
	}
	else if (cmd[1].child == 0)
		command_two(fd, pipefd, cmd, env);
	return (0);
}
