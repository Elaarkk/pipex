/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:59:44 by acolonne          #+#    #+#             */
/*   Updated: 2025/02/17 16:35:35 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	free_cmd(t_cmd *cmd1, t_cmd *cmd2)
{
	if (cmd1)
	{
		if (cmd1->cmd)
		{
			free(cmd1->cmd);
			ft_free_split(cmd1->arg);
		}
	}
	if (cmd2)
	{
		if (cmd2->cmd)
		{
			free(cmd2->cmd);
			ft_free_split(cmd2->arg);
		}
	}
}

void	ft_exit(t_cmd *cmd1, t_cmd *cmd2)
{
	free_cmd(cmd1, cmd2);
	exit(1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd == -1)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	exit_msg(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}

int	close_two_fd(int fd1, int fd2)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	return (0);
}
