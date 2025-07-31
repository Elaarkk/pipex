/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:20:34 by acolonne          #+#    #+#             */
/*   Updated: 2025/02/17 16:34:45 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	pipe_process(int fd[2], t_cmd *cmd, char **env)
{
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		close_two_fd(pipefd[0], pipefd[1]);
		return (-1);
	}
	first_child(fd, cmd, env, pipefd);
	second_child(fd, cmd, env, pipefd);
	close_two_fd(pipefd[0], pipefd[1]);
	if (wait(0) == -1)
		return (1);
	if (wait(0) == -1)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	t_cmd	cmd[2048];
	int		fd[2];

	if (argc != 5)
		exit_msg("Wrong numbers of arguments\n");
	path = get_path(env);
	parse_cmd(&cmd[0], &cmd[1], path, argv);
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] < 0)
		perror("Can't open file");
	fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd[1] < 0)
		perror("Can't open or create file");
	if (pipe_process(fd, cmd, env) == -1)
	{
		perror("Error during commands execution");
		return (1);
	}
	free_cmd(&cmd[0], &cmd[1]);
	close_two_fd(fd[0], fd[1]);
	return (0);
}
