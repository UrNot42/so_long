/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:03:33 by ulevallo          #+#    #+#             */
/*   Updated: 2022/11/26 12:16:33 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_flags(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_fd((char) va_arg(args, int), 1), 1);
	else if (c == 's')
		return (ft_putstrf(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putpf(((uintptr_t)va_arg(args, void *))));
	else if (c == 'd' || c == 'i')
		return (ft_putnbrf((long)va_arg(args, int), 10, '\0'));
	else if (c == 'u')
		return (ft_putnbrf((long)va_arg(args, unsigned int), 10, '\0'));
	else if (c == 'x' || c == 'X')
		return (ft_putnbrf((unsigned int)va_arg(args, int), 16, c));
	else if (c == '%')
		return (write(1, "%", 1), 1);
	else
		return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, s);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			count += ft_printf_flags(s[++i], args);
			i++;
		}
		else if (s[i])
		{
			count++;
			write(1, &s[i++], 1);
		}
	}
	return (count);
}
