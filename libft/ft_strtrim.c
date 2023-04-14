/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:39:31 by ulevallo          #+#    #+#             */
/*   Updated: 2022/11/15 19:09:59 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		start;
	int		end;
	char	*snew;

	start = 0;
	end = ft_strlen((char *)s);
	while (in_set(s[start], set) && s[start])
		start++;
	while (in_set(s[--end], set) && s[end])
		;
	snew = ft_substr(s, start, end - start + 1);
	return (snew);
}
