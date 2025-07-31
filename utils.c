/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:52:52 by acolonne          #+#    #+#             */
/*   Updated: 2025/02/04 15:48:36 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			while ((i + j < len) && big[i + j] == little[j])
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	if (split)
		free(split);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;
	char	*dest;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = malloc(sizeof(char) * (len_s1 + len_s2) + 2);
	if (!dest)
		return (0);
	while (s1[j])
		dest[i++] = s1[j++];
	j = 0;
	dest[i] = '/';
	i++;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	**free_split(char **split, int a)
{
	int	i;

	i = 0;
	while (i < a)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}
