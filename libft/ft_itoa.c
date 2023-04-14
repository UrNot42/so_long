/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:43:28 by ulevallo          #+#    #+#             */
/*   Updated: 2022/11/15 20:23:06 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num(int	*n)
{
	int	rest;

	rest = (*n) % 10;
	*n = (*n) / 10;
	return (rest);
}

static size_t	size(int n)
{
	size_t	len;

	len = 1;
	if (get_num(&n) < 0 || n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		get_num(&n);
		len++;
	}
	return (len + 1);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		r;
	size_t	i;

	i = size(n);
	s = malloc(i * sizeof(char));
	if (!s)
		return (NULL);
	s[--i] = '\0';
	r = get_num(&n);
	if (r < 0 || n < 0)
	{
		s[0] = '-';
		s[--i] = -r + '0';
		n *= -1;
	}
	else
		s[--i] = r + '0';
	while (n > 0)
	{
		r = get_num(&n);
		s[--i] = r + '0';
	}
	return (s);
}
/*
int	main(void)
{
	char *res = ft_itoa(-10);

	printf("%s\n", res);
	free(res);
}
*/
