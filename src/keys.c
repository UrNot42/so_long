/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:53:29 by ulevallo          #+#    #+#             */
/*   Updated: 2023/03/31 00:04:04 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_left(int key)
{
	return (key == 'a' || key == 'h' || key == XK_Left);
}

bool	is_right(int key)
{
	return (key == 'd' || key == 'l' || key == XK_Right);
}

bool	is_up(int key)
{
	return (key == 'w' || key == 'k' || key == XK_Up);
}

bool	is_down(int key)
{
	return (key == 's' || key == 'j' || key == XK_Down);
}

bool	is_start(int key)
{
	return (key == XK_Return || key == ' ' || key == XK_KP_Enter);
}
