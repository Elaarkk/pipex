/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:14:49 by acolonne          #+#    #+#             */
/*   Updated: 2025/02/17 16:04:01 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

char	*copy_cmd(char *src)
{
	char	*cmd_copy;
	int		i;

	i = 0;
	if (!src)
		return (0);
	if (ft_strlen(src) == 0)
		return (0);
	cmd_copy = malloc(ft_strlen(src) + 1);
	if (!cmd_copy)
		return (0);
	while (src[i] && src[i] != ' ')
	{
		cmd_copy[i] = src[i];
		i++;
	}
	cmd_copy[i] = '\0';
	return (cmd_copy);
}

char	*get_cmd(char *cmd)
{
	int		i;
	char	*cmd_cpy;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	cmd_cpy = copy_cmd(&cmd[i]);
	return (cmd_cpy);
}

char	*check_access(char *cmd, char *subpath)
{
	char	*path;

	path = NULL;
	if ((access(cmd, F_OK) == 0) && (access(cmd, X_OK) == 0))
	{
		path = copy_cmd(cmd);
		if (!path)
			return (0);
		return (path);
	}
	if (subpath)
	{
		path = ft_strjoin(subpath, cmd);
		if ((access(path, F_OK) == 0) && (access(path, X_OK) == 0))
			return (path);
		free(path);
	}
	return (0);
}

char	*check_local(char *cmd1)
{
	char	*cmd;
	char	*good_path;

	cmd = get_cmd(cmd1);
	good_path = check_access(cmd, 0);
	if (good_path && cmd)
	{
		free(cmd);
		return (good_path);
	}
	if (cmd)
		free(cmd);
	ft_putstr_fd("command not found\n", 2);
	return (0);
}

char	*check_cmd(char *cmd1, char **path)
{
	int		i;
	char	*cmd;
	char	*good_path;

	i = 0;
	good_path = 0;
	cmd = get_cmd(cmd1);
	while (path[i] && cmd)
	{
		good_path = check_access(cmd, path[i]);
		if (good_path)
		{
			free(cmd);
			return (good_path);
		}
		i++;
	}
	if (cmd)
		free(cmd);
	ft_putstr_fd("command not found\n", 2);
	return (0);
}
