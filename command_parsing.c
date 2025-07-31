/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:25:43 by acolonne          #+#    #+#             */
/*   Updated: 2025/01/30 17:29:18 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

char	**get_path(char **env)
{
	int		i;
	char	**path_list;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_list = ft_split(&env[i][5], ':');
			return (path_list);
		}
		i++;
	}
	return (0);
}

void	parse_cmd(t_cmd *cmd1, t_cmd *cmd2, char **path, char **argv)
{
	if (path)
	{
		cmd1->cmd = check_cmd(argv[2], path);
		cmd2->cmd = check_cmd(argv[3], path);
	}
	else
	{
		cmd1->cmd = check_local(argv[2]);
		cmd2->cmd = check_local(argv[3]);
	}
	if (cmd1->cmd)
		cmd1->arg = ft_split(argv[2], ' ');
	if (cmd2->cmd)
		cmd2->arg = ft_split(argv[3], ' ');
	if (path)
		ft_free_split(path);
}
