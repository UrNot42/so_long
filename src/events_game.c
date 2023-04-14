/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:45:27 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 12:36:09 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Triggers an event based on the current position
 *	of where the player is looking on the map.
 *
 * @param param game parameter structure.
 */
bool	trigger_event(t_params *param)
{
	char	tile;
	t_coord	pos;

	pos = (t_coord){param->p.o.x, param->p.o.y};
	looking_at_coords(&pos.x, &pos.y, param->p.face);
	torus(&pos, &param->size);
	tile = param->map[pos.y][pos.x];
	if (!(is_anim(param->to_animate, pos.x, pos.y))
		&& (tile == DOOR_TILE || tile == DOOR_KEY_TILE))
		open_door(param, pos.x, pos.y);
	if (tile == CHEST_TILE)
		open_chest(param, pos.x, pos.y);
	if ((param->imgs.apo || param->p.god || param->p.sword) && is_enemy(tile))
		kill_enemy(param, pos.x, pos.y);
	if (tile == CHICKEN_TILE && param->p.sword)
		kill_chicken(param);
	if (tile == CHICKEN_TILE && !param->p.sword)
		param->map[pos.y][pos.x] = EMPTY_TILE;
	if ((param->p.sword || param->p.god) && tile == WALL_TILE)
		param->map[pos.y][pos.x] = WALL_TILE_2;
	if (!is_anim(param->to_animate, pos.x, pos.y) && tile == MIMIC_TILE)
		trigger_mimic(param, pos.x, pos.y);
	if (!is_anim(param->to_animate, pos.x, pos.y) && tile == STONE_SWORD_TILE)
		add_element(param->to_animate, &param->imgs.stone, pos.x, pos.y);
	return (true);
}

/**
 * @brief pauses the game
 *
 * @param param pointer to the game variables
 * @return true everything went well
 * @return false error while printing
 */
bool	pause_game(t_params *param)
{
	param->state = PAUSED_STATE;
	param->button = 1;
	param->pressed = false;
	darken_screen(param, 2);
	print_buttons(param, false);
	print_screen(param);
	return (true);
}

/**
 * @brief Adds the stone with a sword sprite element
 *	to the animation queue at the given position.
 *
 * @param param game parameters struct.
 * @param x x-coordinate of the position to add the stone sprite element.
 * @param y y-coordinate of the position to add the stone sprite element.
*/
void	pickup_sword(t_params *param, int x, int y)
{
	param->map[y][x] = STONE_TILE;
	param->p.sword++;
}

/**
 * @brief Adds the door image element
 *	to the animation queue at the given position.
 *
 * @param param game parameters struct.
 * @param x x-coordinate of the position to add the door image element.
 * @param y y-coordinate of the position to add the door image element.
*/
void	open_door(t_params *param, int x, int y)
{
	add_element(param->to_animate, &param->imgs.door, x, y);
}

/**
 * @brief Checks if the player character is killed by an enemy on the map.
 *
 * @param map The game map.
 * @param prm Pointer to the game parameters struct.
 * @return Returns true if the player character
 *	 is killed by an enemy on the map, false otherwise.
*/
int	gets_killed(char **map, t_params *prm)
{
	if (!prm->p.god && is_enemy(map[prm->p.o.y][prm->p.o.x]))
	{
		if (map[prm->p.o.y][prm->p.o.x] == BIRD_TILE)
			death_msg(2);
		if (map[prm->p.o.y][prm->p.o.x] == GHOST_TILE)
			death_msg(3);
		return (finish_map(prm, false), draw_map_image(prm, prm->p.o.x,
				prm->p.o.y, get_img(&prm->imgs,
					map[prm->p.o.y][prm->p.o.x], 0)), true);
	}
	return (false);
}
