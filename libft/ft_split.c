/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:22:08 by ulevallo          #+#    #+#             */
/*   Updated: 2023/03/14 02:48:01 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_parts(const char	*s, char c)
{
	int		i;
	size_t	tot;

	i = 0;
	tot = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] && s[i] == c)
				i++;
		}
		else
		{
			tot++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (tot);
}

static char	*cut(char const *s, char c, int *i)
{
	int		cnt;
	int		j;
	char	*buff;

	cnt = *i;
	while (s[cnt] != c && s[cnt])
		cnt++;
	buff = malloc((cnt - (*i) + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	j = 0;
	while (*i < cnt)
	{
		buff[j++] = s[*i];
		(*i)++;
	}
	buff[j] = '\0';
	return (buff);
}

static void	freeall(char **parts, int j)
{
	while (j >= 0)
		free(parts[j--]);
	free(parts);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	size_t	sum;
	char	**parts;
	char	*buffer;

	i = 0;
	j = 0;
	sum = nb_parts(s, c) + 1;
	parts = malloc(sum * sizeof(char *));
	if (!parts)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			buffer = cut(s, c, &i);
			if (!buffer)
				return (freeall(parts, j), NULL);
			parts[j++] = buffer;
		}
		else
			i++;
	}
	return (parts[j] = NULL, parts);
}
