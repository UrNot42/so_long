/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:35:53 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/12 18:19:10 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_pause_pressed(int key, t_params *param)
{
	if (param->state != PAUSED_STATE)
		return (0);
	param->pressed = false;
	if ((is_start(key) && param->button == 1) || key == 'p')
		param->state = INGAME_STATE;
	if ((is_start(key) && param->button == 3) || key == 'q')
		close_game(param);
	if ((is_start(key) && param->button == 2) || key == 'r')
		restart_game(param);
	return (0);
}

// int	mousse_press(int button, int x, int y, t_params *param)
// {
// 	(void)button;
// 	(void)x;
// 	(void)y;
// 	// div.x = (1 + pos->x * 2);
// 	// div.y = (1 + pos->y * 2);
// 	// size.x = param->mlx.data->width
//	 - (button->width * param->mlx.pxl_size);
// 	// size.y = param->mlx.data->height -
//	 (button->height * param->mlx.pxl_size);
// 	// x = (size.x * div.x) / (6 * param->mlx.pxl_size);
// 	// y = (size.y * div.y) / (6 * param->mlx.pxl_size);
// 	if (param->state != PAUSED_STATE)
// 		return (0);
// 	return (0);
// }

// int	mouse_enter(int button, int x, int y, t_params *param)
// {
// 	(void)button;
// 	(void)x;
// 	(void)y;
// 	if (param->state != PAUSED_STATE)
// 		return (0);
// 	return (0);
// }

// int	mouse_move(int button, int x, int y, t_params *param)
// {
// 	(void)button;
// 	(void)x;
// 	(void)y;
// 	if (param->state != PAUSED_STATE)
// 		return (0);
// 	return (0);
// }
