/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:02:59 by ulevallo          #+#    #+#             */
/*   Updated: 2022/11/15 11:06:44 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	pn;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		pn = -1 * n;
	}
	else
		pn = n;
	if (pn < 10)
	{
		c = pn + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(pn / 10, fd);
		ft_putnbr_fd(pn % 10, fd);
	}
}
