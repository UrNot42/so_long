/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:51:32 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 02:21:16 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Restarts the game.
 *
 * @param param Pointer to the program parameters.
 * @return 0 on success or an error code on failure.
 */
int	restart_game(t_params *param)
{
	if (!param->world.active)
		free_double_str(param->map);
	else
	{
		free_double_str(param->map);
		param->world.maps[param->world.state] = param->map_save;
	}
	param->map = copy_double_str(param->map_save);
	if (!param->map || !set_player(param, param->map))
		return (error_msg(5), close_game(param));
	do_chicken(param, param->map);
	ft_printf(BACK BACK PREV_LN"                                              \n"
		"                                              \n"
		"                                              \n");
	init_parameters(param);
	param->imgs.player.frame = 0;
	draw_map(param, false);
	param->state = INGAME_STATE;
	return (0);
}

/**
 * @brief Handles the game loop.
 *
 * @param param Pointer to the program parameters.
 * @return 0 on success or an error code on failure.
 */
int	game(t_params *param)
{
	if (param->state == INGAME_STATE)
		render_frames(param);
	if (param->state == PAUSED_STATE)
		pause_screen(param);
	if (param->state == WORLD_MAP_STATE)
		display_world_map(param);
	return (0);
}

/**
 * @brief Initializes the map and display, and starts the game loop.
 *
 * @param params Pointer to the program parameters.
 * @param file The path of the map file to load.
 * @return bool Returns true if the initialization is successful,
 *	 false otherwise.
 */
bool	start_map(t_params *param, char *file)
{
	if (!init_map(file, &param->map, 0) || !parse_map(param, param->map))
		return (false);
	if (!init_display(param))
		return (free_double_str(param->map), false);
	if (!so_long(param))
		return (error_msg(5), false);
	return (true);
}

/**
 * @brief Initializes the game and starts the main loop.
 *
 * @param param Pointer to the program parameters.
 * @return bool Returns true if the initialization is successful,
 *	 false otherwise.
 */
bool	so_long(t_params *param)
{
	if (!init_parameters(param))
		return (false);
	ft_printf("\n\n\n");
	param->time_prev = 0;
	print_map(param, false);
	start_mlx_loop_hooks(param);
	return (true);
}
