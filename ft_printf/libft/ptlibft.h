/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptlibft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 03:02:02 by ulevallo          #+#    #+#             */
/*   Updated: 2023/03/14 03:02:03 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTLIBFT_H
# define PTLIBFT_H
# include <stddef.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif
