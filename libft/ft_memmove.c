/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:00:06 by ulevallo          #+#    #+#             */
/*   Updated: 2022/11/15 11:25:58 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t count)
{
	size_t	i;
	int		dif;

	dif = (int *) src - (int *) dst;
	i = (count - 1) * (dif < 0);
	while (i < count)
	{
		((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
		i = i + (1 - 2 * (dif < 0));
	}
	return (dst);
}
