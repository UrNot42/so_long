/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launching_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:05:56 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 02:20:21 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_map(t_params *param)
{
	free_double_str(param->map);
	param->world.maps[param->world.state] = param->map_save;
	if (param->won && (param->world.state + 1 > param->world.completed)
		&& (param->world.completed < param->world.nb_maps))
		param->world.completed++;
	if (param->died)
		param->world.lives--;
	init_parameters(param);
	param->world.dir = SOUTH;
	param->size.x = 6;
	param->size.y = 3;
	param->time_prev = 0;
	ft_printf(RED"=============\n"RESET);
	ft_close_win(param);
	param->mlx.win = NULL;
	init_window(&param->mlx, &param->size);
	start_mlx_win_hooks(param);
	param->state = WORLD_MAP_STATE;
}

int	launch_map(t_params *param)
{
	param->drawn = false;
	if (!parse_map(param, param->world.maps[param->world.state]))
		return (param->world.completed++, 0);
	param->time_prev = 0;
	ft_printf(RED"=============\n   LEVEL "BLUE"%d\n"RED"=============\n\n\n\n"RESET,
		param->world.state + 1);
	ft_close_win(param);
	param->mlx.win = NULL;
	if (!init_window(&param->mlx, &param->size))
		return (false);
	start_mlx_win_hooks(param);
	init_parameters(param);
	print_map(param, false);
	param->state = INGAME_STATE;
	return (1);
}

void	back_to_menu(t_params *param)
{
	param->died = false;
	end_map(param);
}
