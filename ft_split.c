/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:34:38 by acolonne          #+#    #+#             */
/*   Updated: 2025/02/04 15:48:30 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

static int	count_words(char const *s, char c)
{
	int		i;
	char	quote;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == 39 || s[i] == 34)
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
		}
		while (s[i] != c && s[i])
			i++;
		if (s[i - 1] != c)
			count++;
	}
	return (count);
}

static int	count_letter(char const *s, char c, int *i, int *shift)
{
	int		letter;
	int		tmp;
	char	quote;

	*shift = 0;
	letter = 0;
	tmp = *i;
	if (s[tmp] == 39 || s[tmp] == 34)
	{
		quote = s[tmp];
		letter++;
		*i = *i + 1;
		while (s[++tmp] && s[tmp] != quote)
			letter++;
		*shift = letter;
		return (letter - 1);
	}
	while (s[tmp] && s[tmp] != c)
	{
		tmp++;
		letter++;
	}
	return (letter);
}

static char	**assign_split(char **split, char const *s, char c, int words)
{
	int	a;
	int	b;
	int	i;
	int	shift;
	int	size;

	a = 0;
	i = 0;
	shift = 0;
	while (s[i] && a < words)
	{
		b = 0;
		while (s[i] && s[i] == c)
			i++;
		size = count_letter(s, c, &i, &shift);
		split[a] = malloc(sizeof(char) * size + 1);
		if (!split[a])
			return (free_split(split, a));
		while (b < size && s[i])
			split[a][b++] = s[i++];
		split[a++][b] = '\0';
		i += shift;
	}
	split[a] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;

	if (!s)
		return (0);
	words = count_words(s, c);
	split = malloc((sizeof(char *) * (words + 1)));
	if (!split)
		return (0);
	split = assign_split(split, s, c, words);
	return (split);
}
