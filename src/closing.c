/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:51:33 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 02:39:27 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Finish the current game map.
 *	This function draws the player, prints the screen, darkens the screen,
 *	prints the final screen,
 *	sets the game state to 4, and returns 1 to indicate that the map is finished.
 *
 * @param param A pointer to the parameters structure containing screen variables
 * @param win A boolean value that indicates whether the player has won the game.
 * @return int An integer value that indicates whether the map is finished.
 */
int	finish_map(t_params *param, bool win)
{
	draw_player(param, param->p.o.x, param->p.o.y, param->p.face);
	print_screen(param);
	darken_screen(param, 128);
	print_final_screen(param, win);
	param->won = win;
	param->died = !win;
	param->state = FINAL_SCREEN_STATE;
	return (1);
}

/**
 * @brief Close the game and free memory.
 * This function frees the images, sprites, world images,
 * closes the window, destroys the display,
 * ends the MLX loop, frees the memory used by the map,
 * the saved map, and exits the program.
 *
 * @param param A pointer to the parameters structure.
*/
int	close_game(t_params *param)
{
	if (param->world.active)
		param->map = NULL;
	free_imgs(&param->mlx, &param->imgs);
	free_sprites(param, &param->imgs);
	free_world_images(param, &param->world);
	ft_close_win(param);
	if (param->mlx.ptr && param->mlx.win)
		mlx_destroy_display(param->mlx.ptr);
	mlx_loop_end(&param->mlx);
	free(param->mlx.ptr);
	if (param->world.maps)
		free_triple_str(param->world.maps);
	if (param->map)
		free_double_str(param->map);
	if (param->map_save && !param->world.active)
		free_double_str(param->map_save);
	exit(EXIT_SUCCESS);
}
