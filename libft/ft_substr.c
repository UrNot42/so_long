/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:55:30 by ulevallo          #+#    #+#             */
/*   Updated: 2022/11/15 18:45:48 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	a;
	char	*snew;

	a = ft_strlen(s);
	if (start > a)
		a = 0;
	else
		a -= start;
	if (a > len)
		a = len;
	a++;
	snew = malloc(a * sizeof(char));
	if (!snew)
		return (NULL);
	i = 0;
	while (i < (a - 1))
	{
		snew[i] = s[start + i];
		i++;
	}
	snew[i] = '\0';
	return (snew);
}
/*
int main(void)
{
	char	*s = ft_substr("tripouille", 100, 1);
	check(!strcmp(s, ""));
}

*/
