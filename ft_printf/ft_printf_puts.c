/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_puts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:48:20 by ulevallo          #+#    #+#             */
/*   Updated: 2022/11/26 12:15:57 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstrf(char *s)
{
	if (!s)
		return (ft_putstr_fd("(null)", 1), 6);
	else
		return (ft_putstr_fd(s, 1), ft_strlen(s));
}

void	ft_putnbrb(unsigned long n, const unsigned long div, char a)
{
	char	c;

	if (n < div)
	{
		c = n + '0';
		if (n >= 10)
			c = n + a - 33;
		write(1, &c, 1);
	}
	else
	{
		ft_putnbrb(n / div, div, a);
		ft_putnbrb(n % div, div, a);
	}
}

int	ft_putnbrf(long n, int base, char a)
{
	int				count;
	unsigned long	un;

	un = 0;
	count = 0;
	if (n < 0 && !a)
	{
		un = (unsigned long) -n;
		write(1, "-", 1);
		count++;
	}
	else
		un = (unsigned long) n;
	ft_putnbrb(un, base, a);
	un += (!un);
	while (un != 0)
	{
		un /= base;
		count++;
	}
	return (count);
}

int	ft_putpf(uintptr_t p)
{
	if (!p)
		return (write(1, "(nil)", 5), 5);
	else
	{
		write(1, "0x", 2);
		return (ft_putnbrf(p, 16, 'x') + 2);
	}
}
