/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 07:32:58 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 05:07:42 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief initialises basic values to display the world map
 *
 * @param param pointer to the game variables structures
 */
void	init_world_vars(t_params *param)
{
	param->world.maps = NULL;
	param->world.completed = 0;
	param->world.left_lvl_id = 0;
	param->world.nb_maps = 1;
	param->world.player = 0;
	param->world.lives = MAX_LIVES;
	param->world.state = 0;
	param->world.active = true;
	param->world.dir = SOUTH;
	param->size.x = 6;
	param->size.y = 3;
}

/**
 * @brief Initializes the game world variables.
 *
 * This function sets the initial values for
 * various game world variables such as color
 * offsets, completed levels, number of maps, etc.
 * It also initializes the game display,
 * creates a window image and initializes world images.
 *
 * @param prm A pointer to the game parameters structure.
 *
 * @return Returns true if the world variables were successfully
 * initialized, false otherwise.
 */
bool	init_world(t_params *param)
{
	if (!init_parameters(param) || (init_world_vars(param), 0)
		|| !init_display(param) || !init_world_imgs(param))
		return (false);
	return (true);
}

/**
 * @brief Initializes the display and necessary graphics resources for the game.
 *
 * This function sets up the display window using the provided
 * parameters and initializes
 * various image and sprite resources required for rendering the game.
 *
 * @param param A pointer to the game parameters structure.
 *
 * @return Returns true if the display was successfully initialized,
 * false otherwise.
 */
bool	init_display(t_params *param)
{
	param->mlx.name = "so_long";
	param->hex_b = 0;
	param->hex_g = 8;
	param->hex_r = 16;
	param->hex_a = 24;
	if (!init_mlx(&param->mlx, &param->size)
		|| init_images(param->mlx.ptr, &param->imgs)
		|| init_sprites(param->mlx.ptr, &param->imgs))
		return (close_game(param), false);
	param->imgs.player.size /= 4;
	return (true);
}

/**
 * @brief Initializes the player data with default values.
 *
 * This function sets the initial values for various player
 * properties such as direction,
 * number of keys, lives, etc. These values are set to default
 * values to prepare for a new
 * game or level.
 *
 * @param player A pointer to the player structure.
 */
void	init_player_data(t_player *player)
{
	player->face = SOUTH;
	player->keys = 0;
	player->moves = 0;
	player->invis = false;
	player->sword = 0;
	player->god = false;
	player->drunk = 0;
}

/**
 * @brief Initializes the game parameters with default values.
 *
 * This function sets the initial values for various game parameters
 * such as player data,
 * images, animation frames, and color offsets.
 * These values are set to default values to
 * prepare for a new game or level.
 *
 * @param param A pointer to the game parameters structure.
 *
 * @return Returns true if the parameters were successfully
 * initialized, false otherwise.
 */
bool	init_parameters(t_params *param)
{
	init_player_data(&param->p);
	param->imgs.player.frame = 0;
	ft_bzero(&param->prev_input, 11 * sizeof(int));
	param->mv_dir = 0;
	param->state = INGAME_STATE;
	param->time = 0;
	param->drawn = false;
	param->printed = false;
	param->col_ofst = 0;
	param->imgs.apo = false;
	param->imgs.open = false;
	param->won = false;
	param->to_animate[0].sprite = NULL;
	return (true);
}
