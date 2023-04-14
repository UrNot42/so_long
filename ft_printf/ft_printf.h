/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:27:13 by ulevallo          #+#    #+#             */
/*   Updated: 2023/03/14 03:00:01 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft/ptlibft.h"

int		ft_printf(const char *s, ...);
int		ft_putnbrf(long n, int base, char a);
int		ft_putstrf(char *s);
int		ft_putpf(uintptr_t p);
int		ft_printf_flags(char c, va_list args);
void	ft_putnbrb(unsigned long n, const unsigned long div, char a);

#endif
